#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// matrix structure instead of using 2d arrays
struct matrix {
    int row;
    int col;
    int **data;
};
struct node {
    struct matrix mat1;
    struct matrix mat2;
    struct matrix target;
    struct node *next;
};
// utility functions------------------------
struct matrix createMatrix(int row, int col) {
    struct matrix mat;
    mat.row = row;
    mat.col = col;
    mat.data = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++) {
        mat.data[i] = (int *)malloc(col * sizeof(int));
    }
    // Initialize all elements to zero
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mat.data[i][j] = 0;
        }
    }

    return mat;
}
struct matrix createRandomMatrix(int row, int col) {
    struct matrix mat = createMatrix(row, col);
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            mat.data[i][j] = rand() % 1000;
        }
    }
    return mat;
}
void createRandomPair(struct matrix *arr) {
    // array size must be 2 no matter what
    int row1 = (rand() % 200) + 1;
    int col1 = (rand() % 200) + 1;
    int row2 = col1;
    int col2 = (rand() % 200) + 1;

    arr[0] = createRandomMatrix(row1, col1);
    arr[1] = createRandomMatrix(row2, col2);
}
struct node *createNode(struct matrix mat1, struct matrix mat2,
                        struct matrix target) {

    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->mat1 = mat1;
    newNode->mat2 = mat2;
    newNode->target = target;
    newNode->next = NULL;
    return newNode;
}
void insertAtEnd(struct node **head, struct matrix mat1, struct matrix mat2,
                 struct matrix target) {
    struct node *newNode = createNode(mat1, mat2, target);
    if (*head == NULL) {
        *head = newNode;
    } else {
        struct node *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

void freeMatrix(struct matrix matrix) {
    for (int i = 0; i < matrix.row; i++) {
        free(matrix.data[i]);
    }
    free(matrix.data);
}

void freeLinkedList(struct node *head) {
    struct node *temp;
    while (head != NULL) {
        temp = head;
        head = head->next;

        // Free target matrix data (nested frees)
        for (int i = 0; i < temp->target.row; i++) {
            free(temp->target.data[i]);
        }
        free(temp->target.data);

        // Free remaining matrix data and the node itself
        freeMatrix(temp->mat1);
        freeMatrix(temp->mat2);
        free(temp);
    }
}

void printRow(struct matrix matrix, int row) {
    printf("[");
    for (int col = 0; col < matrix.col; col++) {
        printf("%d,", matrix.data[row][col]);
    }
    printf("]\n");
}

void printCol(struct matrix matrix, int col) {
    for (int row = 0; row < matrix.row; row++) {
        printf("%d\n", matrix.data[row][col]);
    }
}

void printMatrix(struct matrix matrix) {
    for (int row = 0; row < matrix.row; row++) {
        printRow(matrix, row);
    }
}
void printLinkedList(struct node *head) {
    struct node *current = head;
    int index = 0;
    while (current != NULL) {
        printf("Node %d:\n", index);
        printf("Matrix 1:\n");
        printMatrix(current->mat1);
        printf("Matrix 2:\n");
        printMatrix(current->mat2);
        printf("Target Matrix:\n");
        printMatrix(current->target);
        printf("\n");
        current = current->next;
        index++;
    }
}

// struct matrix transpose(struct matrix matrix) {
//     struct matrix mat = createMatrix(matrix.col, matrix.row);
//     for (int row = 0; row < matrix.row; row++) {
//         for (int col = 0; col < matrix.col; col++) {
//             mat.data[col][row] = matrix.data[row][col];
//         }
//     }
//     return mat;
// }
// end of utility functions------------------------

// main target of the project matrix multiplication functions to see performance
// increase by using tronsposed matrix
int matMult(struct matrix *target, struct matrix *mat1, struct matrix *mat2) {
    if (mat1->col != mat2->row) {
        return -1; // improper input maritcies
    }
    if (target->row != mat1->row || target->col != mat2->col) {
        return 1; // target size is incorrect
    }
    for (int row = 0; row < mat1->row; row++) {
        for (int col = 0; col < mat2->col; col++) {
            for (int i = 0; i < mat1->col; i++) {
                target->data[row][col] +=
                    mat1->data[row][i] * mat2->data[i][col];
            }
        }
    }

    return 0;
}

void fillLinkedList(int count, struct node **head) {
    struct matrix *arr = (struct matrix *)malloc(sizeof(struct matrix) * 2);
    for (int i = 0; i < count; i++) {
        // Create random matrices
        createRandomPair(arr);
        struct matrix target = createMatrix(arr[0].row, arr[1].col);
        // Insert matrices into the linked list
        insertAtEnd(head, arr[0], arr[1], target);
    }
}

float multiplyMatrices(struct node *head) {
    clock_t start_time = clock();
    struct node *current = head;
    int index = 0;
    while (current != NULL) {
        int res = matMult(&current->target, &current->mat1, &current->mat2);
        if (res != 0) {
            printf("Error: Unable to perform multiplication for node %d using "
                   "standard multiplication.\n",
                   index);
        }
        current = current->next;
        index++;
    }
    clock_t end_time = clock();
    double total_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    return total_time;
}

int main() {
    struct node *head = NULL;
    int count = 2000;

    fillLinkedList(count, &head);

    float total_time = multiplyMatrices(head);

    // printLinkedList(head);
    printf("%f\n", total_time);
    freeLinkedList(head);

    return EXIT_SUCCESS;
}
