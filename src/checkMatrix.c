#include "s21_matrix.h"
int checkMatrix(matrix_t *A, matrix_t *B)
{
    if (A == NULL || B == NULL)
        return INCORRECT_MATRIX;
    if (A->columns != B->columns || A->rows != B->rows)
        return CALCULATION_ERROR;
    return OK;
}