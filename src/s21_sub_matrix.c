#include "s21_matrix.h"
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_null_check(A) != OK || s21_null_check(B) != OK)
    return INCORRECT_MATRIX;
  if (s21_check_rows_columns(A, B) != OK) return CALCULATION_ERROR;
  if (s21_create_matrix(A->rows, A->columns, result) != OK)
    return INCORRECT_MATRIX;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}
