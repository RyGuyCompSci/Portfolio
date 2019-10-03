# N-Sum Partition Problem

- Problem Description

You are a plumbing technician given a box of different lengths of pipe. Your task is to determine if you can make a certain number of equal-length sums of pipe with the given pieces.

- Input

The first line of the input will pair of integers, *N *and* M*.
*N* represents the number of items to work with, and *M* represents the number of partitions the list needs to be split into.

The range of *N* and *M* will be such that *N* = [1,30] and *M* = [1,10].

The last line will be a list *N* integers, each separated by a space. 
This is the input that will be used to determine if *M* partitions of equal sums can be made.
The end of the input will be designated by a 0.

- Output

Output the word "Possible" or "Impossible" to split the *N* items into *M* subsets of equal sums.


- Example

Input:

~~~~~
7 4
1 2 3 4 5 6 7
6 2
1 2 3 4 5 6
0
~~~~~

Output:

~~~~~
Possible
Impossible
~~~~~
