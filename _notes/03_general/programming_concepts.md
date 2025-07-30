---
title: Programming Concepts
layout: note
categories: [General]
---

# What is a program:

## takes an input -> does computation -> gives an output

**Functional programming** more closely follows this paradigm, but computers don't operate like functions but a lot more like turing machines

C -> assembly with syntacting sugar around it  
Haskell -> High level functional language

Languages:
C --> Haskell (fucntional spectrum)
C --> Python (ease of use spectrum)

In the 90s people thought that OOP was going to be this revolutionary programming
C --> C++
This did not actually improve programmer productivity

GC (garbage collection) did

What is a Computer:
Processor (stream of instructions)
RAM (Instruction + Data)

What does a program have:  
text = instructions  
bss = static Data  
stack = local variables (control flow)  

## example:

```c
void a() {
    int variable_on_the_stack;
    // return by popping off the stack
}

void b() {

}

int main() {
    a(); // pushed the return location to the stack

    b();
}
```

heap = malloc

There are different directions you can go with the idea of what is programming
1. practicality (refer ot the practical_proramming file)
 

## What is hacking?

input -> system -> output

What input to the system achieves my desired output?  
The system didn't think to check what it is you are sending in  
You can get the system to behave in ways that aren't within the normal bounds of output

This is like a function like shown below

Pure Model:  
domain -> function -> range  
y = f(x)

Most computation is impure, so the function can output something that is not in the range but can be entirely different

Hacking is figuring out how to make the function behave how you want

CTFs

High brow software engineering
------------------------------

1. Understand a complex system
2. Modify the system to add a feature
3. Ship the new system (test well and stuff)

A lot of contracts and jobs like this

do things like the CLANG for loop challenge that Goerge Hotz did to get good at this

Machine learning engineer 
-------------------------

1. Download a paper
2. Implement it 
3. Keep doing this until you have skills

> " There is no such thing as wasting time. Wasting time is great. That is the point of time, to waste it. " 
Goerge Hotz


If you are learning object level skills you are learning the wrong thing. They will die out when the tools die out.  
Learning meta level skills -> truths about the world

Build a knowledge tree
----------------------

- New information fits into the tree
- Interpolation is possible when getting new information in the tree 
  - Even if you don't know a node of the tree you can know nodes nearby and interpolate
- Framework for understanding

### examples: 
- Elon roots knoweledge tree in physics
- Goerge roots knowldege tree in information

One test to use often to ask a question oiff somebody is saying something:  
say if anybody would say the opposite.  
What is a good work ethic to have?  
slack off, not pay attention  

meaningless question

-----------
does there exist a more concise programming language?

aka. what is the next GC?

compilers should do more search.




