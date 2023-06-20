#include "s21_matrix.h"
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int errorState = checkMatrix(A, B);
    if (errorState != OK)
        return errorState;
    errorState = s21_create_matrix(A->rows, A->columns, result);
    if (errorState != SUCCESS)
        return errorState;
    for (int i = 0; i < A->rows; i++)
    {
        for (int j = 0; j < A->columns; j++)
        {
            result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
    }
    return errorState;
}