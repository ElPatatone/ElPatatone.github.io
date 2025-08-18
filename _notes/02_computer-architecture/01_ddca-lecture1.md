---
title: Introduction to computer architecture 
slug: introduction-to-computer-architecture
categories: [Hardware]
layout: note
---

## Levels of Abstraction

- Problem
- Algorithm
- Program/Language
- System Software (VM, OS, MM)
- ISA (architecture): interface between the software and hardware
- Mircroarchitecture: implementation of the ISA
- Logic: digital logic circuits
- Devices
- Electrons

It is difficult to change the **ISA** as a lot of software is built on top of it, 
**mircroarchitecture** is easier to change. 

Different platforms can achieve different goals:
- TPU: machine learning focused workflows
- CPU: general computing
- GPU: parallel computing

But there is also a focus on the software used on these platforms to optimize things.
We should work on every part of the system.

### What is Computer Architecture?
It is the science and art of designing, selecting and interconnecting hardware 
components and designing the hardware/software interfaces to create a computing 
system that meets our goals.

**Enable better systems**: make computers faster, cheaper, smaller, more realiable
**Enable new applications**: self-driving cars can only happen on modern hardware 

We have been using databases for decades and they are getting bigger each year. Scaling
them is hard to do if we do not have better systems to manage the bigger workload.

Richard Feynman said: "There's plenty of room at the bottom"

Meaning we should focus on the underlying technology and the foundations.

## Transistors
They are the building blocks of computers.
- **Intel 4004** in 1971 had **2300 MOS transistors**  
- **Intel Pentium IV** in 2000 had **42 Million MOS transistors**  
- **Apple M2 Max** in 2022 had **67 Billion MOS transistors**  

## MOS Transistors
made with combining:
- **Metal** - conductors
- **Oxide** - insulators 
- **Semiconductors**

Combine many of them and we get simple logic gates.
 
[look up]
electrical properties of metal-oxide semiconductors
Sections 1.6/1.7 of H & H

Example:
- for a lamp to glow electrons must flow 
- for electrons to flow there must be a closed circuit from the power supply to the 
  lamp and back to the power supply
- the lamp can be turned on and off by using the wall switch to make or break the 
  closed circuit

There are 2 types of **MOS transistors**:

**n-type**: if the gate of the transistor is supplied with high enough voltage, 
the connection from the source to drain acts like a wire, the circuit is closed.

**p-type**: uses the same structure as a **n-type** transistor but the logic is 
inverted. If there is no voltage being passed in then the circuit is closed.

Small volts are good for low energy, ideally people want to reduce the voltage to 
not waste energy.
However the issue is that with small voltages the noise margin is smaller. Trying 
to distinguish between **0V and 0.3V** is much harder than **0V and 3V**.   
Reducing the voltage makes things less reliable.

## Logic gates
**Logic gates** implement simple boolean functions 

[look up]
george boole paper

Modern computers use both the **n-type** and **p-type** transistors.
Complementary MOS, CMOS

**PMOS** transistors are good at pulling up the output. 
**NMOS** transistors are good at pulling down the output. 

### CMOS NOT Gate
- if A = 0V then Y = 3V -> 1
- if A = 3V then Y = 0V -> 0

| A | PMOS | NMOS | Y |
| - | - | - | - |
| 0 | ON | OFF | 1 |
| 1 | OFF | ON | 0 |

This can be summarised with the following:

$$

Y = \overline{A}

$$

### CMOS NAND Gate

| A | B | P1 | P2 | N1 | N2 | Y |
| - | - | - | - | - | - | - |
| 0 | 0 | ON | ON | OFF | OFF | 1 |
| 0 | 1 | ON | OFF | OFF | ON | 1 |
| 1 | 0 | OFF | ON | ON | OFF | 1 |
| 1 | 1 | OFF | OFF | ON | ON | 0 |

- **P1 and P2** are in **parallel**, only one must be on to pull up the output to 3V 
- **N1 and N2** are connected in series, both must be on to pull down the output to 0V

$$

Y = \overline{A \cdot B} = \overline{AB}

$$

### CMOS AND Gate

This gate can be made by taking the output of the **NAND** gate and passing it into 
a **NOT** gate. 

$$

Y = A \cdot B = AB

$$

## Resources
- [DDCA lecture 1](https://www.youtube.com/watch?v=ubhxKNlOlRg&list=PL5Q2soXY2Zi9Eo29LMgKVcaydS7V1zZW3&index=1) 
