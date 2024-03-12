# DPLL SAT Solver

## Overview
This SAT Solver incorporates a series of components to process and solve Boolean formulas. Initially, the Solver uses a Tokenizer and Parser to verify the syntax of the Boolean formula, converting it into Negative Normal Form to reduce multiple negations. This approach helps in minimizing new variables during the Tseitin Transformation, thereby saving time. The final output is a Boolean formula in CNF, which the DPLL Solver addresses using unit-resolution propagation and a naive truth table method for a depth-first search approach on the assignment tree.

I implemented a data structure specific for constant retrieval for current assignment, the LinkedHashMap.



## Usage
Explain how to use the software, including any command line arguments or configurations.

```sh
./eval.sh
```

## DPLL Implementation
The DPLL algorithm is implemented according to specific pseudo-code references, focusing on maintaining loop invariants for each recursive call in BCP (Boolean Constraint Propagation) and PLP (Pure Literal Propagation). The software utilizes a "vector of vectors" for CNF formulas and integrates STL's queue and hashmap for assignment maps, ensuring FIFO access and constant-time lookup. This method significantly optimizes performance by preventing duplicate assignments and maintaining order in variable assignments.

## Time and Space Efficiency
The solver is designed with time and space efficiency in mind. At each recursive call, it maintains a new CNF and an assignment map, both bounded by the number of connectives and variables. On average, the memory used is tightly bound and less than the worst-case scenario. Performance metrics on the ECE-Tesla Server indicate significant efficiency in terms of runtime and memory usage.

## Future Work
- Addressing memory leaks by implementing missing destructors.
- Transitioning from nested vectors to graph structures for representing CNFs.
- Developing classes for variables, literals, clauses, and CNFs to enhance modularity and readability.









