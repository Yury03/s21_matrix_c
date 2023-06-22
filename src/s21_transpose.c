#include "s21_matrix.h"
int s21_transpose(matrix_t *A, matrix_t *result) {
  if (s21_null_check(A) != OK) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->columns, A->rows, result) != OK)
    return INCORRECT_MATRIX;
  for (int i = 0; i < result->columns; i++)
    for (int j = 0; j < result->rows; j++)
      result->matrix[i][j] = A->matrix[j][i];
  return OK;
}