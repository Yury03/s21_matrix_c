#include "s21_matrix.h"
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  if (s21_null_check(A) != OK) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++)
    for (int j = 0; j < A->columns; j++)
      result->matrix[i][j] = A->matrix[i][j] * number;
  return OK;
}