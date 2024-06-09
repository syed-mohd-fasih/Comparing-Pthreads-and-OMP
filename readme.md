# Comparison of Pthreads and OpenMP in Sorting Algorithms

## Project Overview

This project aims to compare the performance of Pthreads and OpenMP in implementing various sorting algorithms. The sorting algorithms used in this study include:

- Bubble Sort
- Selection Sort
- Merge Sort
- Binary Insertion Sort
- Cocktail Sort

The objective is to analyze and understand the differences in execution time, scalability, and efficiency between these two parallel programming models.

## Table of Contents

1. [Introduction](#introduction)
2. [Setup and Requirements](#setup-and-requirements)
3. [Code Structure](#code-structure)
4. [Implementation Details](#implementation-details)
5. [Running the Code](#running-the-code)
7. [Conclusion](#conclusion)

## Introduction

Parallel computing is essential for improving the performance of computationally intensive tasks. In this project, we utilize Pthreads and OpenMP to parallelize five sorting algorithms. By comparing their performance, we aim to identify the strengths and weaknesses of each approach in the context of sorting.

## Setup and Requirements

### Prerequisites

- GCC Compiler with OpenMP support
- Basic knowledge of C/C++ programming
- Understanding of multithreading concepts

### Installation

1. Ensure GCC is installed on your system. You can install it using your package manager. For example, on Ubuntu, use:
    ```sh
    sudo apt-get install gcc
    ```

2. Clone this repository to your local machine:
    ```sh
    git clone https://github.com/your-repo/sorting-algorithms-comparison.git
    cd sorting-algorithms-comparison
    ```

## Code Structure

The project directory is structured as follows:

```
sorting-algorithms-comparison/
│
├── src/
│   ├── bubble_sort_pthreads.c
│   ├── bubble_sort_omp.c
│   ├── selection_sort_pthreads.c
│   ├── selection_sort_omp.c
│   ├── merge_sort_pthreads.c
│   ├── merge_sort_omp.c
│   ├── binary_insertion_sort_pthreads.c
│   ├── binary_insertion_sort_omp.c
│   ├── cocktail_sort_pthreads.c
│   ├── cocktail_sort_omp.c
│
├── README.md
```

## Implementation Details

### Bubble Sort

- **Pthreads Implementation**: `src/bubble_sort_pthreads.c`
- **OpenMP Implementation**: `src/bubble_sort_omp.c`

### Selection Sort

- **Pthreads Implementation**: `src/selection_sort_pthreads.c`
- **OpenMP Implementation**: `src/selection_sort_omp.c`

### Merge Sort

- **Pthreads Implementation**: `src/merge_sort_pthreads.c`
- **OpenMP Implementation**: `src/merge_sort_omp.c`

### Binary Insertion Sort

- **Pthreads Implementation**: `src/binary_insertion_sort_pthreads.c`
- **OpenMP Implementation**: `src/binary_insertion_sort_omp.c`

### Cocktail Sort

- **Pthreads Implementation**: `src/cocktail_sort_pthreads.c`
- **OpenMP Implementation**: `src/cocktail_sort_omp.c`

## Running the Code
### Executing the Programs

Each sorting algorithm can be executed separately. Here are examples of how to run the Pthreads and OpenMP implementations of Bubble Sort:

```sh
./bubble_sort_pthreads
./bubble_sort_omp
```

Repeat the process for other sorting algorithms by replacing `bubble_sort` with the desired algorithm name.

## Conclusion

This project highlights the differences between Pthreads and OpenMP in terms of performance and ease of implementation for various sorting algorithms.
This repository only contains the source code to the implementation of each sorting algorithm in Pthreads and OpenMP.