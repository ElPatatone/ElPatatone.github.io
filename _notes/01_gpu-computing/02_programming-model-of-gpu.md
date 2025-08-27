---
title: Programming model of GPUs using CUDA 
slug: programming-model-of-gpus-using-cuda
categories: [GPU-Computing]
layout: note
---

## Types of Parallelism
**Task Parallelism**: different operations performed on the same or different data  
- Example: text editor that has spellchecker on top. Different operations done at the 
same time on the same data.  
- usually has a modest number of tasks unleashing a modest amount of parallelism
    - because in one application how many differnt type of operations would you run 
      at the same time

**Data Parallelism**: same operations performed on different data   
- Example: a screen where we render different pixels, same operations but different 
data used.
- potentially massive amounts of data unleashing massive amounts of parallelism
    - taking the same program and running it on a larger dataset, like rendering 
      an image on a higher resolution screen
    - most suitable for **GPUs** 

## System Organization
**CPU**: host 
**RAM (main memory)**: host memory  

**GPU**: device 
**(device memory)**: global memory 

The CPU and the GPU have seperate memories and cannot access each others memories  
We can use **PCie** to transfer the data across the two, another way which is specific
to Nvidia is **Nvlink**. 

Steps:
1. allocate GPU memory
2. copy data from CPU memory to GPU memory
3. perform computation on GPU
4. copy data from GPU memory to CPU memory
5. deallocate GPU memory


## Vector addition
sequential code:
```c
for (int i = 0; i < arraySize; i++) {
    c[i] = a[i] + b[i];
}
``` 
To make this operation faster on the GPU, we can assign a **thread** per vector 
element so we can run all the computation in parallel instead of sequentially.

**grid** is an array of **threads**  
**block** is a group of **threads** inside a **grid**   

[look up] threads in the same block can collaborate in ways that threads in different
          blocks cannot

## Launch a grid
- threads in the same grid execute the same function known as a **kernel**  
- grid can be launched by calling a kernel and configuring it with appropriate 
  block and grid sizes  

[look up] Current maximum number of threads per block in modern GPUs is
**1024**    

keywords:
**gridDim.x**: number of blocks in the grid 
**blockIdx.x**: position of blocks in the grid along the x-axis 
**blockDim.x**: number of threads in the block 
**threadIdx.x**: position of the thread in the block along the x-axis 

To find the global index of a thread based on all the threads in the grid  
you do the following:
**blockDim.x * blockIdx.x + threadIdx.x** 

This is very important to remember.

In the case of vector additions, we need to find the global index of a thread 
because we want to assign each thread to an element of the vector by matching their 
index.

## Compilation with NVCC
Splits the code into 2 parts.
C/C++ compilation:
1. host C/C++ code is passed into the host C/C++ compiler
2. host assembly is generated
    - host assembly (e.g x86, ARM)
3. device assembly is run on the CPU 

CUDA compilation:
1. CUDA code is compiled into **.ptx** a virtual **ISA**  
2. device **Just-in-Time compiler** takes the **.ptx** and compiles it to device assembly 
    - happens when we run the program, **runtime** 
    - device assembly (e.g SASS)
3. device assembly is run on the GPU 

When we have a call to the kernel the CPU will call the device assembly code to 
run on the GPU. 

kernels are **asynchronous**

## What is CUDA?
The way graphics works is very similar to the way other domains works but with 
different emphasis. 
CUDA started with supercomputing but now it is heavily used in 
the AI world as well.

CUDA is written in C, started out as a language in a compiler. It is now much more 
than just a language, it has a lot of different things going on.

It is essentially an abstraction, a python function that does image processing runs 
CUDA in the background

CUDA sees the CPU and the GPU as one -> heterogeneous computing (using more than one
type of processor, CPU and GPU)

example program:
1. Load the config file in the CPU
2. Fetch an API from the interntet on the CPU
3. Do some image processing on the GPU

We as the programmer are able to tell CUDA where the instructions go, it will look 
like one program on the surface.

CUDA allows communication between the CPU and GPU using the PCIE buses. 
But there is something called confidential computing from Nvidia where there is a 
fully encrypted channel that encrypt the communication on the PCIE buses.

CUDA is like an interpreter as it takes in the commands that you give it and it turns 
them into the command streams that the hardware needs to control it.

Originally GPUs were made to push pixels onto a screen.
There are these deep pipelines for graphical processing, but it turns out that
pipelines for pixers are the same as pipelines for matrix operations for AI and other 
things.

1. compilers create the binary files
2. runtimes that control the hardware to dispatch the binary to them
3. assembly language to actually run the program

CUDA can take in many different types of software and it interacts with different type
of hardware.

It then it makes the software think there is only one type of hardware and the makes
the hardware think there is only one type of software.

## References
- [PMPP lecture 2](https://www.youtube.com/watch?v=iE-xGWBQtH0&list=PLRRuQYjFhpmubuwx-w8X964ofVkW1T8O4&index=2)
- [What is CUDA - computerphile](https://www.youtube.com/watch?v=K9anz4aB0S0&t=169s)
