#include "s21_matrix.h"
int s21_create_matrix(int rows, int columns, matrix_t *result)
{
  if (!result || columns <= 0 || rows <= 0)
    return INCORRECT_MATRIX;
  result->rows = rows;
  result->columns = columns;
  result->matrix = malloc(rows * sizeof(double *));
  for (int i = 0; i < rows; i++)
  {
    result->matrix[i] = malloc(columns * sizeof(double)); // инициализация calloc
  }
  return OK;
}