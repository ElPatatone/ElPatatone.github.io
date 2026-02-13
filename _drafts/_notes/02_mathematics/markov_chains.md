---
title: "Understanding Markov Chains"
categories: [Mathematics]
math: true
layout: note
---

So I was watching this [video](https://www.youtube.com/watch?v=_d3z2wVtDD8). 

It went over the concept of Markov chains and bigrams to help create the generative
language model. Seemed like pretty cool topics and after looking them up a bit I am 
interested in working on a project using those concepts.

From what I understand, Markov chains are one of primary foundations of the modern 
language models.

## What is a Markov chain?
A **Markov chain** is a stochastic process that satisfies the **markov property**:
> The probability of the next state depending only on the current state, not on the 
full history of past states.

Formally expressed as:

$$
P(X_{n+1} \mid X_n, X_{n-1}, \ldots) = P(X_{n+1} \mid X_n)
$$

This means that knowing the present state $X_n$ is enough to predict the next state 
$X_{n+1}$ as well as if you had access to the entire past.
This has to be conditional on both past and present values.

## What is a bigram?
A **bigram** is a specific application of a first-order Markov chain in linguistics,
used to model sequences of words. It predicts the current word based solely on the
immediately preceding word. 

Bigram:

$$
P(w_i \mid w_{i-1})
$$

There are also **higher-order markov models** such as trigrams: 

$$
P(w_i \mid w_{i-2}, w_{i-1})
$$


## Why people shifted the notation from traditional markov chain to n-order markov chain like a bigram

The goal in NLP is to predict the next word in the sequence. The question that is 
asked is: **"What is the probability of this word, given the words that came 
before".**  

This leads to the following notation being used:

$$
P(w_1 \mid w_{i-1})
$$  

Where the previous words are treated as the known context (input) and the current 
word is the target being predicted.

In contrast, traditional markov chains follow the question: **"Given the current
state, what is the probability of the next state."** 

It is just a matter of how they decided to frame the problem in their respective 
domains, which is why the notation differs.


### NEXT STEPS 
- look into the evolution of markov chains, **hidden markov models(hmm)** 
- think of a project to use markov chains. Very cool topic.
- Interesting articles to read:
    - [1](https://www.danieleteti.it/post/from-markov-chains-to-modern-llms/#best-practices-and-pitfalls) 
    - [2](https://medium.com/data-science/markov-models-and-markov-chains-explained-in-real-life-probabilistic-workout-routine-65e47b5c9a73) 
    - [3](https://web.stanford.edu/~jurafsky/slp3/) 
