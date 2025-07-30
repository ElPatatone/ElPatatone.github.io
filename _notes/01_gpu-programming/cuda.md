---
title: What is CUDA?
categories: [GPU-Programming]
layout: note
---

GPU is designed to go really fast and parallel
high throughput paralized processing

1. write a GPU kernel (CUDA code)
2. copy some data from the main RAM into the GPU RAM
3. CPU then tells the GPU to executes the code
4. final output in the GPU RAM is copied into the main RAM

GPU has thousands of cores

What problems are good for GPUs?
- any problem that can benefit from mass parallization
- scalarize a large set of vectors

```c++
// code run on the CPU is done in a serialized order
// c is the output vector

for(int i = 0; i < N; i++){
    c[i] = a[i] + b[i];
}

// code run on the GPU is done in parallel

void vectorAdd(int *a, int *b, int *c) {
    int i = someMagicValue;
    c[i] = a[i] + b[i];
}
```

A kernel is something that abstracts the layer between the CPU and GPU.
kernel -> grid -> block -> thread

A lot of different domains use GPUs.

fixed-function hardware was how GPU started. Now it is flipped

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

CUDA is something like a kernel.
