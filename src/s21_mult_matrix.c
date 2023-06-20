#include "s21_matrix.h"
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result)
{
    int resulting_code = OK;
    if (!result || !A || !B)
    {
        resulting_code = INCORRECT_MATRIX;
    }
    else if (A->columns == B->rows)
    {
        s21_create_matrix(A->rows, B->columns, result);
        for (int i = 0; i < result->columns; i++)
        {
            for (int j = 0; j < result->rows; j++)
            {
                result->matrix[i][j] = 0;
                for (int k = 0; k < A->columns; k++)
                {
                    result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
                }
            }
        }
    }
    else
    {
        resulting_code = CALCULATION_ERROR;
    }
    return resulting_code;
}