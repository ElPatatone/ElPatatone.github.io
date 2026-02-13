---
title: Why does CUDA work the way it does?
slug: why-does-CUDA-work-the-way-it-does?
categories: [GPU-Computing]
layout: note
---

## How does memory work in the GPU?
A single bit of memory is a capacitor, either on or off. The memory is read by 
switching a transistor on which is connected to the wire, the wire will in turn carry
a voltage based on the charge from the capacitor.

The **DRAM** chip contains millions of this cells that are all connected together 
in a 2D matrix. You can access data in any of the rows and columns in this matrix 
giving the property of **random access memory**. The data has a row and column index.

[look up]  
DRAM and how it reads memory

1. pull data from the desired row into the **sense amplifiers**, the sense amplifiers
   take the small charge from the capacitors in the memory cell and turn it into 
   easier to read, more defined voltages for the next steps.
   The capacitors are drained of their charge through this process so the data in the 
   capacitors is deleted as a result.
2. read from the data stored in the amplifiers at the desired column index, this
   does not delete the data in the amplifiers. Reading data from the amplifiers is also
   much quicker and easier as the amplifiers produce a stronger and clearer signal.
3. you can read as many times as you want from the amplifiers as the data is not being
   deleted, **burst mode** is a single request to read multiple data that is adjacent 
   in the same row. Less expensive then sending multiple requests through.
4. When a new row needs to be read, the current row in the sense amplifiers has to be 
   written back because the data was originally destroyed in the memory cells. This 
   is an expensive operation as you have to write back and then read a new row. 
   About 3 times more expensive then just reading a new column in the same row.

The rate it takes to read and load data from the DRAM is dependant on the physical 
time it takes to charge and discharge capacitors.

Data read patterns matters because of the physics of the random access memory.

## So what does this all mean?
As the stride gets larger you start to read elements in different **pages (rows)** in 
the HBM. You have to constantly switch the capacitors on and off to load the pages 
creating a massive drop in memory bandwidth.

The memory access patterns are extrememly important because it can provide the biggest
boost in performance for GPUs. A 10 TFLOPs **A100** can be fed at rates of **GFLOPs**
instead with bad memory access patters, making the use of the A100 just pointeless at 
that point.

The reason we use GPUs is for performance and to get that performance we need to 
efficiently manage all of those GPU resources.

## Inside a Streaming Multiprocessor
Each SM has a maximum memory bandwidth, that is why the GPU will load blocks into all 
the SMs to make sure that it is able to make the most of the full GPU memory bandwidth.

All blocks in the grid will run the same program using the same number of threads,
and they need 3 things:
- **block size**: the number of threads in each block 
- **shared memory**: high speed memory pool that all threads in the block can use 
- **registers**: working space of the thread, immiedately accessible by the thread for 
                 operations. All threads will be running the same program so each 
                 thread will have the same registers size (threds per block * 
                 registers per thread = total registers count per block)

## How does the GPU place blocks in an SM?
The GPU places blocks into SMs until one of the resources (threads, registers, shared
memory, or block limit) is exhausted. We call this **occupancy**.

Having multiple blocks per SM is crucial, because it enables latency hiding: when one
warp stalls on memory, another warp can be scheduled instantly. If only one block is
resident, latency hiding is severely limited, and performance suffers.

Therefore, after ensuring efficient memory access (e.g. coalesced reads/writes), the
next big lever is tuning occupancy, by adjusting block size, shared memory usage, and
register pressure to maximize throughput. 

## What can we do with the gaps in the SM?
The gpu will try to run another grids blocks in the SMs as long as those new blocks 
resource requirements are lower than the remaining resources in the SM.

This is done with **concurrency**. 

We can divide independent pieces of work into seperate **streams** and then the GPU 
can try and pack them into the SMs. It may not be able to start working on the blocks 
from different streams at the same time, due to resource limitations, but it can 
load a block from another stream causing the work timeline for that stream to be 
different than the original stream.

The SM will then just start going through all of the blocks it has in it and keep on 
loading new blocks and doing their computation once the resources are freed up, this
is the process of **oversubscription**. 

## Conclusion
1. memory system can only feed a fraction of what the compute units can process
2. the memory system itself depends on good access patterns, coalesced memory
3. warp execution systems can counter this slow down by reading more than one thread 
   at once. But we need all the threads in the warp to be reading memory adjacent to 
   each other.
4. the hardware spreads the blocks as widely as possible so all the SMs are being 
   utilized, giving us a higher memory bandwidth.
5. resource packing limitations have the next biggest imapct on performance
6. to counter this we need to feed more data concurrently to the SM through multiple 
   streams.
7. CUDA works the way it does because of physics.

## References
- [How CUDA programming works (GTC 2022)](https://www.youtube.com/watch?v=n6M8R8-PlnE&t=1631s) 
- [CUDA programming guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/contents.html)
- [Ampere microarchitecutre](https://en.wikipedia.org/wiki/Ampere_(microarchitecture)) 
- [A100 whitepaper](https://images.nvidia.com/aem-dam/en-zz/Solutions/data-center/nvidia-ampere-architecture-whitepaper.pdf) 
