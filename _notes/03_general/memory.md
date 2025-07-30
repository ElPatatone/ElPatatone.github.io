---
title: Deep dive into memory
categories: [Hardware]
layout: note
---

## Breaking down the structure of memory
The `main()` function starts a chain of function calls.
When running the program the OS gives us a slice of the memeory in the RAM. 
It gives us the `process memory layout`: 

STACK -> where all the action takes place  
HEAP  -> memory allocated at run time/dynamically  
.DATA -> initializesd global and static variables  
.BSS -> unitialized global and static variables  
.TEXT -> machince code  

Creating a variable means turning bits on and off somewhere in the RAM.

```c 
int main() {
    int nb;
    nb = 42;
}
```

`nb` is a local variable that lives in the stack, inside the `main()` function frame.
The memory address provided to the variable is in actuality a `virtual address`. 

Whenever the program reaches a new function, it is then allocated space in the STACK.
Each function gets a `stack frame`. 

The `stack frame` contains the following:
- Return address (where to go back to resume the program after the function call)
- Parameters passed to the function
- Local variables made in that function
- Saved copies of registers (base and frame pointers)

These 2 are stored in CPU registers:
`stack pointer (rsp/esp)` points to the current top of the `stack frame`.
`base pointer (rbp/ebp)` points to the start of the current `stack frame`. 

The `STACK` grows downwards, meaning new frames are placed at a lower memory address.
It grows towards the `HEAP` using the free space between the 2 of them. 

When a function returns the following happens:
- Its frame is popped off the `STACK` and the memory is freed up 
- `stack pointer` is adjusted 
- `base pointer` is restored 

This continues until even the `stack frame` for the `main()` function is 
removed from the `STACK` and the program ends. 

CPU registers and caches


