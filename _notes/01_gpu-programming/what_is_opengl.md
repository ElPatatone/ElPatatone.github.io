---
title: What is OpenGL?
categories: [GPU-Programming]
layout: note
---

## What is OpenGL
OpenGL is a series of graphics commands, functions that we can call as it is a **c** 
programming based API. It allows us to interact with the **GPU**, load data and render 
it from the **GPU** instead of the **CPU**.  

It is a specification that represents how a graphics API should look like.

## History of OpenGl
1. In 1991 SGI starts developing OpenGL.
    - runs on multiple platforms (windows, linux, mac etc)
2. Version 1.1 supports texturing and has a **Fixed Function Pipeline**. 
3. Version 1.5 starts pushing OpenGL **Extensions (Shaders)**.
    - **Architecture Review Board** allowed companies to start sending in extensions 
      based off on their hardware.
4. Version 2.1 starts enforcing a **programmable pipeline** with GLSL language.
    - We as programmers are able to write and execute programs on the **GPU**. 
    - We are able to offload the work on to the **GPU** instead of only relying on the 
      **CPU**. 
5. Version 3.3/4.0 starts removing the old functionality
    - Only the **programmable pipeline** is used. 
6. Version 4.6 is what we use today.

## Graphics Pipeline
A rendering pipeline is the following:
- The journey of a primitive(vertex, triangle, line, etc) from their 3D data to a 
  2D plane, our screen for example.

How would **point(1.0,0.0,-5.0)** look like on our screen? 

### 1. Vertex Specification
Where we setup our vector data on the **CPU**. 

### 2. Vertex Shader 
**Shader**: programmable part of our pipeline. 
This is a feature of modern OpenGL that we can write programs on our **GPU** to control
the graphics pipeline.

In the beginning we were not able to change the data being set to the **GPU**. 

It executes on each vertex, positioning that vertex.

### 3. Tesselation (optional)
The process of breaking up bigger primitives into smaller primitives to create more 
detail in the rendering.

### 4. Geometry Shader (optional)
The process of generating more geometry from a given point on the **GPU**.
- useful for particle systems
- explosion effect

### 5. Vertex Post-Processing
Here you can do additional post processing for the data.
Example: you create new points in using the **geometry shader**, you can then process 
that data right after.

### 6. Primitive Assembly
Assembling the final geometry by taking in all the data from the vertices.
Includes other phases too:
- clipping: clips primitives if they are outside of the specified bounds.
- face culling: removes the faces of the primitive that are not necessary for the 
                rendering.

### 7. Rasterization
The process of drawing in the actual pixels based on the vertices that we have loaded 
in so far.
- **depth test**: deciding what to do if shapes overlap

### 8. Fragment Shader
It executes once on each fragment -> sort of like a pixel.
Determine the final color of each of the pixels that we rasterize.

### 9. Pre-Sample Operation
Different operations can be done here as the last step.


