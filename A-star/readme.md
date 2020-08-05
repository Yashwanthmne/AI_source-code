# TSP using A*

## Problem:

Given a list of cities and the distances between each pair of cities, what is the shortest possible route that visits each city and returns to the origin city?

## State Space

**State:** List of cities

**Start State:** Salesman in the start city and has not visited any other city

**Goal State:** Salesman has visited all the cities and reached the start city again

**Action:** Add new city that have not yet visited

**Cost:**

**1. Edge Cost:** Distance between the cities represented by the nodes, use this cost to calculate g(n).
	
**2. Heuristic Cost:** Distance to the nearest unvisited city from the current city + estimated distance to travel all          the unvisited cities (MST heuristic used here) + nearest distance from an unvisited city to the start city. **This is an 	admissible heuristic function.**


## Compile and Run
```
g++ TSP.cpp
./a.out
```

## Input & Output

**Input Instruction:** Code can be configured to accept custom inputs, however for ease of use, I have hard coded a graph.

