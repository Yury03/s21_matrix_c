#include "s21_matrix.h"


int compareDoubles(double a, double b)
{
    return fabs(a - b) < 0.0000001
               ? SUCCESS
               : FAILURE;
}
int s21_eq_matrix(matrix_t *A, matrix_t *B)
{
    int isEquals = SUCCESS;
    if (A->columns == B->columns && A->rows == B->rows)
        for (int i = 0; i < A->rows && isEquals; i++)
            for (int j = 0; j < A->columns && isEquals; j++)
                isEquals = compareDoubles(A->matrix[i][j], B->matrix[i][j]);

    return isEquals;
}