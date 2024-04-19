## Matrix Multiplication with Linked List and GCC Optimization Flags

This project aims to evaluate the performance increase achieved by utilizing GCC optimization flags such as `-O3` and `-flto` (link-time optimization) in matrix multiplication implemented with a linked list data structure in C.

## Objective

The primary objective of this project is to compare the performance of matrix multiplication with and without GCC optimization flags. By leveraging optimization techniques provided by GCC, we seek to observe potential improvements in execution time and resource utilization.
the mean run time for each executable is given bellow 
Mean from output/output_dev.txt: 7.68689330000000000000
Mean from output/output_lto.txt: 1.47289646000000000000
Mean from output/output_o1.txt: 3.57933184000000000000
Mean from output/output_o2.txt: 1.48266066000000000000
Mean from output/output_o3.txt: 1.46832738000000000000



## Features

- Creation of random matrices with variable sizes.
- Multiplication of matrices using standard multiplication algorithm.
- Printing of matrices and linked list contents.
- Measurement of time taken for matrix multiplication.

## Requirements

-gcc 

## How it Works

1. The program creates a linked list of matrix multiplication tasks.
2. Random matrices are generated and inserted into the linked list.
3. Matrices are multiplied using standard multiplication algorithm.
4. The time taken for matrix multiplication is measured and printed.
5. Result matrices and the linked list contents are printed.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details. This project is created to see the performance increase using the gcc optimization flags suchas -O3 and -flto
