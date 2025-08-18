---
title: GPU execution model 
slug: gpu-execution-model
categories: [GPU-Computing]
layout: note
---

## GPU Architecture
A **GPU** has multiple **streaming multiprocessors (SMs)** and each one of those 
consists of multiple **cores** with shared **control** and **memory**.   
They all then have access to **global memory**. 

The **SMs** can only accomodate a limited number of **threads** at once as they 
in turn need resources to execute their tasks. In the case where the **grid** 
launched has more **threads** than the whole **GPU** can run at once, then the 
remaining **threads** wait for other **threads** to finish before they start running.  

### Synchronization
**threads** in the same **block**, **SM**, can work together in certain ways.  
- **barrier synchronization**: `__syncthreads()` waits for all threads in the block 
  to reach a certain point in the code before any thread can continue.
- **shared memory**: access fast memory that only threads in the same block can access
- threads in different blocks do not work with each other, each block is independent
  from each other
    - enables **transparent scalability**, the same code can be run on different 
      devices with different hardware specs
      - one machine with few SMs can run blocks sequentially
      - another machine with more SMs can run blocks in parallel
- there is no context switching at the block level, the block is executed until all
  the threads inside of it are done and only then is a new block brought into the SM 
  to run its own threads

### Thread Scheduling
Threads assigned to an SM run concurrently, there is a scheduler that manages their 
execution.  
They are then divided further into **warps** which are the unit of scheduling, groups
of 32 threads. 

**SIMD** has a disadvantage, different threads take different control paths, resulting
in **control divergence**. When a point is reached where the threads need to branch
in their control paths, instead of having the threads that are not taking that branch
moving on and going in their own path, all of the threads will travel together.
If one thread is not taking branch 1 it will still go to that branch and be inactive
and then once the threads at branch 1 are done they will all go to branch 2.

The percentage of threads that are active during SIMD is called **SIMD efficiency**. 

### Latency Hiding
When a warp is waiting for a high latency operation, another warp can be scheduled 
for execution.

**occupancy**: ratio of threads active on the SM compared to the maximum allowed.
- generally maximising this ratio is the goal to improve latency hiding
- choosing the correct block size

I look at this concept in more detail [here](/notes/gpu-computing/why-data-location-matters-in-gpu-computing/)  

> If you want your processors to have low latency then you optimize how long
operations take, but if you want your processors to have high throughput then you want
to have more cores and will tolerate the higher latency.

## Resources
- [PMPP lecture 4](https://www.youtube.com/watch?v=pBQJAwogMoE&list=PLRRuQYjFhpmubuwx-w8X964ofVkW1T8O4&index=4) 
