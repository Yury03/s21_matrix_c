#include "s21_matrix.h"
int s21_create_matrix(int rows, int columns, matrix_t *result)
{
    int errorState = SUCCESS;
    if (rows <= 0 || columns <= 0 || result == NULL)
    {
        errorState = FAILURE;
    }
    else
    {
        result->matrix = (double **)malloc(rows * sizeof(double *));
        for (int i = 0; i < rows; i++)
        {
            result->matrix[i] = (double *)malloc(columns * sizeof(double));
        }
        result->rows = rows;
        result->columns = columns;
    }
    return errorState;
}