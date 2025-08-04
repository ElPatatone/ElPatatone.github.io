---
title: Binary in computing 
categories: [Hardware]
layout: note
---

## Basics of Binary

decimal -> base 10
binary -> base 2

binary have **LSB(Least Significant Bit)** and **MSB(Most Significant Bit)** 

negative numbers in binary can be done with 3 methods:
- signed magnitude
- one's complement
- two's complement -> method used right now

## Signed Magnitude
To show the signature of a number in binary, the **MSB** is used as the **sign bit** where
**0** is positive and **1** is negtive.  

The rest of the bits are called the **magnitude**.

This is the first method that was used to handle negative numbers but there are 2 
drawbacks:
1. There are 2 versions for representing the value **0**. 
2. The arithmetic is messy.

## One's Complement
The **sign bit** is still the **MSB**.  

To represent the negative representation of a number, we flip the bits.
Example:  
Number 5  
Positive binary = 0101  
Negative binary = 1010

If there is a carry-out from the MSB, we perform an **end-around carry**, adding the
carry bit back into the LSB.

This solves the issue with arithmetic operations with **one's complement** but it 
still leaves the issue with the 2 versions of representing the value **0**.

## Two's Complement
The **sign bit** is still the **MSB**.  

To write **-5** we do the following:
1. Flip the bits -> 5 = 0101 becomes 1010
2. Add 1 to the binary number -> 1010 + 1 = 1011 = -5
3. During the operation, we can use all the bits without worrying about the sign 
   bit, but when we finish we have to remember the sign bit of the original binary 
   number and make the decimal value postive or negative based on that.

We can prove that the binary **1011** is **-5** the following:
1. Flip the bits again -> 1011 becomes 0100
2. Add 1 to the binary number -> 0100 + 1 = 0101 = 5

If there is an extra carry after adding a negative and postive binary number we can 
just ignore it.

This solves the arithmetic issue completely and the **0** problem. 

We only use this method if we know that the binary given is a signed value.

# Binary in Computing

Computers use **8-bits** values which is **1-byte**.  
Binary is used in several ways in computers.

## Instruction Encoding

- CPU reads instruction as binary (in **.text** section).
- Instruction format varies by ISA (Instruction Set Architecture):
    - x86: variable-length (1–15 bytes)
    - RISC-V, ARM: fixed-length (e.g., 32 bits)
- An instruction can be broken into:
    - Opcode (what to do) like:
        - ADD = 101
        - MOVE = 100
    - Register specifiers (operands)
    - Immediate values
    - Addressing mode bits

## Memory/RAM
    - Memory is **byte-addressable** where each unit is **1-byte** = **8-bits**    
    - Each byte has an address associated to it

## Information from hardware
Hardware like keyboards uses cables that transfer the information of what keys 
are being pressed and that can be seen as bits. 

## How does a CPU understand the instructions?
An instruction is a binary-encoded command to the CPU that consists of:
- **opcode**: tells the CPU what to do 
- **operands**: tells the CPU what to do it with 

We use **decoding** to tell the CPU how to deal with instructions. 

Example **opcodes**:

| Operation | Binary |
|------|----|
| MOVE | 01 |
|ADD| 10 |
|HALT| 11 |
|NO ACTION | 00 |


They will have different components tied together making decisions based on the 
current being passed in.

When the CPU reads an instruction, it extracts the **opcode** and sends it to all
the different **decoders** (subsystems for all the instructions). 

When the correct decoder is found then it will trigger its subsystem to carry out the 
operation.

With the following example instruction:
```
010111
01 = Opcode for MOVE operation
01 = source address
11 = destination address
```

Once the **MOVE** decoder receives the extracted **opcode**, it will then move the data 
in address **01** to the address **11**.  

Good to know:
When we talk about a **64-bit** computer:
- how many bits are available for a single memory address.
- the **bus width** which is the amount of wires connecting the different units 
  inside a computer.
- the size of **registers** (memory cells inside the CPU) the fastest memory inside
  of a computer. 


