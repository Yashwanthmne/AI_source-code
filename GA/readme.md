# Genetic Algorithm

## Problem

Given N student, distribute into K groups such that diversity is minimize using the marks of M subjects.

## Explanation

**Chromosome:** Generate random marks of *N* student in *M* subjects and store into 2D array.

**Population:** Randomly select 50 chromosome for Initial population which divided into *K* groups and Group Representative is average value of group.

**Fitness Value:** Take absolute value of difference of group representative and student's marks.

**Selection:** Select two parent by Tournament Selection.

**Crossover:** choose a random point and do single point crossover.

**Mutation:** Randomly select a gene from each chromosome of the crossover population and mutating/changing with random group representative to increase diversity.

*Replace the old population by the new generated population by following above steps.*

*The loop will be break until loop count greater than 2000 or previous fitness value is greater than current fitness value*

## Run

javac GA.java
java GA

## Input & Output

**Input Instruction:** Please follow on screen instruction
**Output File:** output.txt

