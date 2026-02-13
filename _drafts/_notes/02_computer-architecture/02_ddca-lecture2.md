---
title: Looking at logic gates
slug: looking-at-logic-gates
categories: [Hardware]
layout: note
---

## Latency
**transistors** in series are slower than ones in parallel because there is more 
resistence on the wire.

[look up]  
1.7.8 of H&H
psuedo-nMOS logic

## Power Consumption
**Dynamic Power Consumption** is the power used to charge **capacitance** as signals
change, 0 to 1.

**capacitance** is a measure of how much electric charge can be stored per volt across
2 conductors seperated by an insulator.
[look up]
look more into the capacitance and electrical side of things

C*V**2 * f

- C = capacitance of the circuit (wires and gates)
- V = supply voltage
- f = charging frequency of the capacitor

When increasing **f** we want to also increase **V** to achieve the oputput for **f**.
Voltage has a cubical affect on power.

**Static Power Consumption** is the power consumed when the circuit is idle.
V * I leakage

**energy consumption** is 

power * time  

need to include both dynamic and static power

### Larger gates
We can extend gates to more than 2 inputs but this leads to increased latency. It 
would be better to just seperate the larger gate into smaller gates and combine the 
output.

## How do we keep Moore's Law?
1. manufacturing smaller transistors/structures
    - some structures are already a few atoms in size
2. using materials with better properties
    - copper instead of aluminium (better conductor)
    - hafnium oxide, air for insulators
    - making sure all materials are compatible is the challenge
3. enable precision manufacturing
    - extreme ultraviolet (UEV) light to pattern <10nm structures
4. creating new device technologies
    - FinFET, gate all around transistro, single electron transistor

[look up]
- microelectronic design
- precision manufacturing
- fabrication technologies
- IEDM
- extreme ultraviolet litography
- Moores law paper

**Innovation at the bottom enables computing.**

### How do we make a logic circuit?
A logic circuit is composed of:
- inputs
- ouputs
- specifications

**Functional specification** describes relationship between inputs and outputs 
**Timing specification** describes the delay between inputs changing and outputs 
responding

### Types of a logic circuit
**combinational logic**:
- memoryless (we don't remember what we have done with the inputs to make the outputs)
- outputs are strictly dependant on the combination of input values that are being 
  applied to the circuit right now

**sequential logic**:
- has memory
- outputs are determined by previous and current value of inputs

## Boolean Algebra
Boolean algebra is important because if we were to implement a circuit for a very 
complex boolean formula, the resulting circuit could be extremely expensive. 
Instead we can simplify the boolean formula, thus reducing the circuits complexity as 
well.

[look up]  
axioms + proofs
george boole - the mathematical analysis of logic
go explore boolean algebra

**duality** in boolean algebra means that every axiom opposite form is true as well. 

[look up]  
logic/hardware synthesis course - simplify circuits
**DeMorgans law**: enabling transformation 

### Why care about Boolean Algebra?
- It helps us represent the function of a combinational logic block
- transform the function into simpler functions
    - leads to different hardware realizations
    - logic minimization or logic simplification
    - we can automate the process with computer aided design or electronic design 
      automation
- different boolean expressions lead to different logic gate implementations
    - different hardware, cost, latency, energy properties

### Standardized function representations
A universally agreed way of representing these boolean functions.


**Sum of Products (SOP)**  
SUM(OR) of all products (minterms) that cause output to be 1.    
- AND = product | OR = sum
- create a truth table for the inputs
- find all the input combinations (minterms) where the output is TRUE
- the function is 1 if any of the input combinations is 1, we do not care for the rest

If 0 then complement the variable  
if 1 then keep as is

We can shorten this by enumerating each row with the decimal value of the binary 
number made with the inputs.
This way we do not need the truth table and instead can create an expression that 
represents it.

But then we always have to get the minimal form for the canonical form of the 
boolean expression.

**Product of Sums (POS)**   
- find all the input combinations where the output is FALSE  
- the function is 0 if any of the input combinations is 0, we do not care for the rest

If 1 then complement the variable  
if 0 then keep as is

## Combinational logic
- It is often grouped into larger building blocks to build more complex systems  
- hides the unnecessary gate level details to emphasise the function of the building 
  block, creates abstraction for easier building.

### Decoder
- input pattern detector
- n inputs and 2^n outputs
- exactly one of the outputs is 1 and all the rest are 0 - one hot encoding
- used in memory, instruction decoding, I/O selection
Example 2:4 decoder  

### Multiplexer (MUX)
- selects one of the n inputs to connect it to the output
Example 2-to-1 MUX has 2 data inputs and 1 select input.   
If select input is 0 then selects D0, if select input is 1 then selects D1  
- can be used as look up tables to perform logic functions

**Programmable logic array (PLA)** enables the 2 level SOP implementation of any 
N-input M-output function.  

[look up]  
ripple carry adder  
lookahead adder

## References
- [DDCA lecture 2](https://www.youtube.com/watch?v=U-4jmbm8inw&list=PL5Q2soXY2Zi9Eo29LMgKVcaydS7V1zZW3&index=2) 
