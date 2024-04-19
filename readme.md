## Evaluating GCC Optimization Flags for Matrix Multiplication with Linked Lists

This project aims to assess the performance improvements achieved through GCC optimization flags such as `-O3` and `-flto` in a matrix multiplication implementation utilizing linked lists in C.

### Objective

Our primary objective is to compare the execution times of matrix multiplication with and without GCC optimization flags. By leveraging GCC's optimization techniques, we aim to observe potential enhancements in execution speed and resource utilization.

### Results

The mean run times for each executable are as follows:
- `-dev`:7.68689330000000000000 seconds
- `-O1`: 3.58 seconds
- `-O2`: 1.48 seconds
- `-O3`: 1.47 seconds
- `-flto`: 1.47 seconds

### Key Features

- Creation of random matrices with variable sizes.
- Matrix multiplication using standard algorithms.
- Printing of matrices and linked list contents.
- Measurement of matrix multiplication time.

### Requirements

- GCC bc

### How it Works

1. The program generates a linked list of matrix multiplication tasks.
2. Random matrices are created and added to the linked list.
3. Matrix multiplication is performed using standard algorithms.
4. The program measures and displays the time taken for matrix multiplication.
5. Result matrices and linked list contents are printed for inspection.

### License

This project is licensed under the MIT License. Refer to the [LICENSE](LICENSE) file for details.

