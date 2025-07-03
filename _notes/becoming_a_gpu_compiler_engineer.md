---
name: Becoming a GPU compiler engineer
references: https://www.reddit.com/r/Compilers/comments/1g4fnbg/becoming_a_gpu_compiler_engineer/
---

[Link to the post](https://www.reddit.com/r/Compilers/comments/1g4fnbg/becoming_a_gpu_compiler_engineer/)

@dnpetrov
- As a GPU engineer you will do a lot of optimizations, supporting new hardware
  features and fixing bugs.
- Need some fundamental understanding of what the compiler actually does after it 
  dealt with the source language.
- Good books on the subject: Optimizing Compilers for Modern Architectures: A
  Dependence-Based Approach by Ken Kennedy and Randy Allen 
- Many tuorials on YouTube that cover important topics in LLVM framework architecture.
- Focus on LLVM IR.

@roeschinc
- Best way to get started is to go and work on compilers in open source or elsewhere 
  to gain experience.

@sirfmaths
- For GPU the most important part is the middle end where all the optimization such as
  vectorization, loop interchange, tiling, buffer allocation will happen
- Compiler course will likely teach SSA which is essential to understand LLVM and MLIR
- Most GPU compiler positions are for AI compilations.
- Read up on ONNX.

- I used to work at some of the companies you mentioned. We had a few new
  undergraduates. Don’t worry about your degree, read up on the source language,
  architectures, LLVM and C++. That is good enough to get hired as a junior.

- Things that helped me break into the field: computer graphics (OpenGL, VL, DX)
  basics, CUDA and OpenCL source language, parallelism, good C++ experience, 
  knowledge of NVidia GPUs from their CUDA programming model, ability to read 
  and understand ISAs, LLVM and compiler knowledge.

- Oh yeah, skip the courses about parsers. No one cares about parsing. Most of the
  problems will be require knowledge of the source language and IR transformations.
  Often times the front end team focuses more on optimizations or tooling

@Strict_Shopping_6443
- Recommend diving deeper into LLVM & MLIR even if it's just side projects and you 
  don't feel ready yet to make commits to the main repos.
- Look into the weekly LLVM office hours.
- Check out Trito, Numba and Halide.

@WittySuck
- At the low level the main difference is that GPU compilers target a different
  instruction set.
- AMD -> RDNA - current most recent public spec is v3.5
- NVidia -> PTX/SASS - limited public docs
- LLVM has backends for both of these ISAs, making it the most practical tool to use 
  for targeting the GPU.
- AMD docs are superior as it provides instruction encodings.
- NVidia instructions encodings have no official public docs.
- LLVM CUDA backend still depends on the SDK from NVidia for machine code generation.


