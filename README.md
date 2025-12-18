# Disclaimer
Since writing this script, I recognize that this is not the correct way to do parallelization of this kind of task. This just served as my entryway to Open-MPI and parallel computing.

# OpenMPI-MergeSort
Using OpenMPI for C++ to sort array chunks in parallel.

`parallel.cpp` sorts a list of 1,000,000 random integers from 0-100 using multiple processors calling mergeSort.

`sequential.cpp` sorts a list of 1,000,000 random integers from 0-100 using normal mergeSort.

OpenMPI is required to compile and run `parallel.cpp`

# Testing
In testing with the list of 1,000,000 integers, I observed a 9x-10x speed improvement by the parallel program compared to the sequential program. This might be dependent on the technology used. It should also be noted, that not much of an improvement was seen when testing with small amounts of integers. (i.e. 10 and 100)

# Inspiration
I've been meaning to learn Parallel computing and OpenMPI, so as a beginner project, I rewrote and adapted the code from my previous Final Project for my [CSCI-4345 Computer Networks](https://github.com/RodolfoJGonz/CSCI-4345-Final-Project) course. That project consisted of leveraging a server-client collection to merge sort a list of integers using the client's computers.
