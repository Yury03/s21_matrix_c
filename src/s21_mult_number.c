#include "s21_matrix.h"
int s21_mult_number(matrix_t *A, double number, matrix_t *result)
{
    int errorState = checkMatrix(A, A); // для проверки на NULL
    if (errorState != OK)
        return errorState;
    errorState = s21_create_matrix(A->rows, A->columns, result);
    if (errorState != SUCCESS)
        return errorState;
    for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < A->columns; j++)
            result->matrix[i][j] = A->matrix[i][j] * number;
    return errorState;
}