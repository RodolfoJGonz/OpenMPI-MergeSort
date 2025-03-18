# OpenMPI-MergeSort
Using OpenMPI for C++ to sort array chunks in parallel.

`parallel.cpp` merges a list of 1,000,000 random integers from 0-100 using multiple processors calling mergeSort.

`sequential.cpp` merges a list of 1,000,000 random integers from 0-100 using normal mergeSort.

OpenMPI is required to compile and run `parallel.cpp`

# Testing
In testing with the list of 1,000,000 integers, I observed a 9x-10x speed improvement by the parallel program compared to the sequential program. This might be dependent on the technology used.

# Inspiration
I've been meaning to learn Parallel computing and OpenMPI, so as a beginner project, I rewrote and adapted the code from my previous Final Project for my [CSCI-4345 Computer Networks](https://github.com/RodolfoJGonz/CSCI-4345-Final-Project) course. That project consisted of leveraging a server-client collection to merge sort a list of integers using the client's computers.
