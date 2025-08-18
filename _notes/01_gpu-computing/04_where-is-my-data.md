---
title: Why data location matters in GPU computing
slug: why-data-location-matters-in-gpu-computing
categories: [GPU-Computing]
layout: note
---

## Where is my data
Nobody cares about **FLOPS (Floating Point Operations per Second)**, or we shouldn't 
really care about it.

$$ 
\text{Compute intensity} =  \frac{\text{FLOPS}}{\text{Data Rate}}  
$$

Hardware design focuses on increasing the raw compute capacity, the peak FLOPS.
Software design focused on maximising the utilization of hardware to actualise the 
peak FLOPS.

**NVIDIA A100**:
- peak FP64 GFLOPS: 19500
- memory bandwidth (GB/sec): 1555
- compute intensity (FP64): 100

Every single generation we can add **computing power** faster than **memory bandwidth**. 
[look up]  
memory wall problem

So we should really care about the **memory bandwidth**, **latency**.  
Pipelining is a key concept in todays computing optimisations because the **memory 
latency** is huge compated to the **compute latency**.  

### But why is that?
Physics.  
- speed of light = 300'000'000 M/s 
- computer clock = 3'000'000'000 Hz (3Ghz)
- speed of electricity in silicon = 60'000'000 M/s 

In a single clock tick light travels **100mm**. Electricity travels **20mm**. 
So based on the die size of the chip that could be 1/2 clock ticks of electricity just
travelling from one side to the other.  

The way the **transistors** are pipelined also affects the speed of electricity, aka.
the speed of loading and reading memory.

example scenario:  
Daxpy:

$$
\alpha X+Y = Z
$$

**Intel Xeon 8280**:
- memory bandwidth: 131 GB/s 
- memory latency: 89 ns

[look up]  
the roofline model

How many bytes travel per socond:

$$
\text {Bytes travelled} = \text{Memory Bandwidth} \times \text{Memory Latency}
$$

You have to convert the values in seconds:

$$
\text{Bytes travelled} = (131 \times 10^{9}) \times (89 \times 10^{-9}) = 131 \times 89 = 11659 \text{ bytes}
$$

In the example scenario a **daxpy** operation moves **16 bytes** per **89ns** latency. 
Giving us a **memory efficiency** of **0.14%**.  
This happens when the program is **latency bound**. 
Compilers can do **loop unrolling** to improve this but there are still limits to it. 
There is a limit to how many things the hardware can stage in the pipeline before 
it has to wait for things to come back.
Plus we are still using 1 thread for all of these.

### So how do we improve the performance?
We use parallelism.  
We can use **threads** to issue load operations independently but in parallel. 
Looking at the example scenario, we are able to cover up for the low **memory 
efficiency** by using a GPU like the **NVIDIA A100**.  

The **NVIDIA A100** has 2 versions, the full implementation and the **TensorCore** 
implementation. The lecture goes over the **TensorCore** version which has the 
following specs:
- 108 SMs
- 64 FP32 CUDA cores/SM 
- 4 third-generation Tensor Cores/SM 
- registers file size 256 KB/SM - 27MB/whole GPU 
- 192KB L1 cache/SM - 20MB/whole GPU
- 40MB L2 cache/whole GPU

(specs taken from [A100 whitepaper](https://images.nvidia.com/aem-dam/en-zz/Solutions/data-center/nvidia-ampere-architecture-whitepaper.pdf))

### Memory in a GPU
Compared to a **CPU** a **GPU** has long latency between each one of its different 
caches. So it uses a large amount of registers in each thread to keep live data 
around at a low latency. These registers are also used by the hardware to store data
that has been loaded into memory for operations, so the number of registers we have 
on a **GPU** directly relates to the number of memory operations we can be doing. 

**GPU** use registers as a buffer to hide and avoid latency. 

For the **NVIDIA A100** it means the following:
- 27MB = 27'000'000 bytes = 3'375'000 FP64 values

Why do we care so much about memory on the GPU?  
Because using the **PCIe** to move memory is the biggest bottleneck by far. That is 
why we try to keep the memory local.

### Oversubscription
It has more threads/warps than it can actually use per clock cycle so that when some 
threads are waiting because of latency, other threads have already received their 
response and are ready to go.

The **GPU** can switch from one warp to the next in a single clock cycle.  

This is how you compensate for the latency, you have more threads alive than the system
can run at a given time.

Opposite of what you would do on a **CPU**. 

**NVIDIA A100** specs based on the **CC 8.0**:
- 2048 threads/SM
- 64 warps/SM 
- 4 active warps/SM (4 warp schedulers, but it does not mean all 4 are running in 
parallel)

Doing these things beats latency. But we still are being limited to bandwidth. Beating
compute intensity is all about scaling the problem.

### Matrix multiplication
This is the one algorithm that can fight the compute intensity.

We want more **FLOPS** to go faster but that also means that we need bigger problems
to work on or the memory system becomes the bottleneck.  

Data location matters a lot to tackle compute intensity.  
example compute intensity for **matmul** operation on TF32: 
- **HBM**: 400
- **L2 Cache**: 156
- **L1 Cache**: 32 

Below are the minimum sizes of a matrix to meet the demands of the compute intensity:
- **HBM**: 400
- **L2 Cache**: 150
- **L1 Cache**: 32

So although a **TF32** has higher **FLOPS** meaning it has a higher base compute 
intensity, we can offset this and meet those requirements by deliberately choosing 
where we are placing the data in the memory.

### Conclusion
1. **FLOPS** don't matter but **memory bandwidth** does because of **compute
     intensity**.  
2. **memory bandwidth** does not really matter because **memory latency** is long. 
3. To fix **latency** we need a lot of **threads** and **GPUs** do that.   
4. To get high efficiency on small compute intensity pieces of work, we just have 
   be more deliberate with where the data is stored.
5. **memory latency** can be beaten with **threads** and **memory bandwidth** can be 
   beaten with locality.
6. Then we can get all the **FLOPS** even from **TF32** 
7. The ability to max out the efficiency of all the components in the system is linked
   to where the data is located to begin with.

Even if we have 5000GB/s memory bandwidth, it won't matter if the latency is 5s due 
to the data being stored in the HBM, if we cannot move the data closer to the 
compute units then we will never be able to make us of all the FLOPS the GPU has.

### Resources
- [How GPU computing works? Stephen Jones, GTC 2021 ](https://www.youtube.com/watch?v=3l10o0DYJXg&t=64s) 
- [CUDA programming guide](https://docs.nvidia.com/cuda/cuda-c-programming-guide/contents.html)
- [Ampere microarchitecutre](https://en.wikipedia.org/wiki/Ampere_(microarchitecture)) 
- [A100 whitepaper](https://images.nvidia.com/aem-dam/en-zz/Solutions/data-center/nvidia-ampere-architecture-whitepaper.pdf) 
