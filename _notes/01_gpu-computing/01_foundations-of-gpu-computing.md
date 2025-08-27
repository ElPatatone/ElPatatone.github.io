---
title: Why did we need GPUs 
slug: why-do-we-need-gpus
categories: [GPU-Computing]
layout: note
---

# Introduction
**Moores law** is the prediction that the numbers of **transistors** per unit area
would double every **18-24 months**.

This was been true until **2005**. 

The transistors are getting harder to make smaller due to the physical limitations.  
[look up] why is it actually getting harder? -> physics was an issue, heat became too 
high to realistically rely on cooling to solve the problem

When they get smaller it is easier to switch them on and off faster, so we can 
increase the clock **frequency** faster.

The **frequency (clock rate)** followed the same trend as a result but this lasted only 
until 2005.

Even if the transistors were doubling we stopped trying to increase the frequency
because it takes more power to do this. Burning more power generates more heat thus 
needing cooling or the CPU would begin melting.

There was a bottleneck because of the cooling technology we had.

Single thread performance also started to stagnate but because of compiler advancements
and improvements in architecture there were still some improvements.
[look up] speculative execution, branch prediction, out of order execution

Because the single thread performance was stagnating but we were still getting more 
transistors. We started to use extra transistors to make the **CPU** cores more
complex, better at single threaded performance, we hit physical and architectural
walls (power, **ILP (Instruction-Level Parallelism)**, heat). So we began to use those
transistors to build many simpler **cores** with more **ALUs**, focused on parallelism
rather than per-core complexity.

This all happened at around **2005**.

Before the slow down in single thread performance, it was possible to just see massive
performance gains by running an older program on a new processor. However, to now see
performance gains in software it was now required to update programs to take advantage
of parallel processing.

## Design approaches
**Latency-Oriented Design**: minimize the time it takes for a single task  
**Throughput-Oriented Design**: maximise the number of task that can be performed in 
                              a given time frame

**CPU**: Latency-Oriented Design
- has few powerful **ALU** to reduce operation latency
- large **caches** reduce the missrate of the CPU,  
- sophisticated **control units** for branch prediction to reduce control hazards 
    - data forwarding to reduce data hazards
    - out-of-order operation to reduce latency

[look up] n-bit multi cycle and single cycle
          why do smaller ALUs give higher latency for operations? 

**GPU**: Throughput-Oriented Design 
- ALU are much smaller and have higher latency but have higher throughput. 
[look up] Heavily pipelined for further throughput.
- small caches so we can dedicate more area in the silicon to compute
    - memory access operations take longer as a result
- simpler control units so we have more area dedicated to computation

minimize stalls in the pipeline with scheduling instructions with compiler techniques.

On the hardware side we can do out-of-order ROB [look up]
they can also do **multithreading** to hide short latency
- use the same **core** to execute multiple **threads** 
- **hyperthreading** commonly uses 2 threads running at the same time in the same 
  core 
- CPU have a modest amount of multithreading  

On the GPU we have a massive number of threads to hide the high latency  
- many more cores means more threads that can be used
- more threads can be used on the same core, instead of just 2 we could use 32  

CPU have high clock frequency while GPU have moderate clock frequency  

## What is a GPU
In graphics we don't care about the speed at which we can render 1 pixel, we care more
about rendering as many pixels as possible at the same time.

People realised that `GPUs` althought built for graphics, were actually great at 
general purpose computing as well. However, before 2007 there were only graphics APIs
to program on `GPU` like openGL. 

So people had to reformulate their computation as functions that operate on pixels to 
do their operations.

NVIDIA then released `CUDA` as a result. A programming interface to use the power of 
`GPUs` in a general purpose way. 
This still required extensions to the `GPU architecture`. 

2007 marks the beginning of the modern computing era.

## Why did GPUs succeed?
Chips are very expensives to build and require a large volume of sales to balance 
the costs.
- this makes the chip market hard to get into and succeed in 
- when parallel computing becamse mainstream, `GPUs` were already being used in the 
  gaming sector so it gave them a large head start compared to other potential 
      massively parallel accelerators

One issue is that because the gaming sector is the largest market share for `GPUs`,
if there is a new advancement that could improve performance in scientefic computing 
but would negatively impact the performance in gaming, the likelyhood of the
manufacturer going ahead with it is low. 

[look up] tenstorrent

## References
- [PMPP lecture 1](https://www.youtube.com/watch?v=4pkbXmE4POc&list=PLRRuQYjFhpmubuwx-w8X964ofVkW1T8O4&index=1) 
