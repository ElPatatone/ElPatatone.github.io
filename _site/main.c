#include <assert.h>   // for assert
#include <stdbool.h>  // for bool
#include <stddef.h>   // for NULL
#include <stdint.h>   // for int32_t, etc
#include <string.h>   // for memcpy
#include <sys/mman.h> // for mmap

#include "greatest.h"

// Objects

typedef int64_t word;
typedef uint64_t uword;

const int kBitsPerByte = 8;                        // bits
const int kWordSize = sizeof(word);                // bytes
const int kBitsPerWord = kWordSize * kBitsPerByte; // bits
const unsigned int kIntegerTag = 0x0;
const unsigned int kIntegerTagMask = 0x3;
const unsigned int kIntegerShift = 2;
const unsigned int kIntegerBits = kBitsPerWord - kIntegerShift;
const word kIntegerMax = (1LL << (kIntegerBits - 1)) - 1;
const word kIntegerMin = -(1LL << (kIntegerBits - 1));

word Object_encode_integer(word value) {
  assert(value < kIntegerMax && "too big");
  assert(value > kIntegerMin && "too small");
  return value << kIntegerShift;
}

// End Objects
typedef unsigned char byte;

typedef enum {
  kWritable,
  kExecutable,
} BufferState;

typedef struct {
  byte *address;
  BufferState state;
  size_t len;
  size_t capacity;
} Buffer;

byte *Buffer_alloc_writable(size_t capacity) {
  byte *result = mmap(/*addr=*/NULL, /*length=*/capacity,
                      /*prot=*/PROT_READ | PROT_WRITE,
                      /*flags=*/MAP_ANONYMOUS | MAP_PRIVATE,
                      /*filedes=*/-1, /*offset=*/0);
  assert(result != MAP_FAILED);
  return result;
}

void Buffer_init(Buffer *result, size_t capacity) {
  result->address = Buffer_alloc_writable(capacity);
  assert(result->address != MAP_FAILED);
  result->state = kWritable;
  result->len = 0;
  result->capacity = capacity;
}

void Buffer_deinit(Buffer *buf) {
  munmap(buf->address, buf->capacity);
  buf->address = NULL;
  buf->len = 0;
  buf->capacity = 0;
}

int Buffer_make_executable(Buffer *buf) {
  int result = mprotect(buf->address, buf->len, PROT_EXEC);
  buf->state = kExecutable;
  return result;
}
// AST

struct ASTNode;
typedef struct ASTNode ASTNode;

ASTNode *AST_new_integer(word value) {
  return (ASTNode *)Object_encode_integer(value);
}

bool AST_is_integer(ASTNode *node) {
  return ((word)node & kIntegerTagMask) == kIntegerTag;
}

word AST_get_integer(ASTNode *node) { return (word)node >> kIntegerShift; }

// End AST
