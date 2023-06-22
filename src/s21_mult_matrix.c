#include "s21_matrix.h"
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (s21_null_check(A) || s21_null_check(B)) return INCORRECT_MATRIX;
  if (s21_create_matrix(A->rows, B->columns, result) != OK)
    return INCORRECT_MATRIX;
  int resulting_code = OK;
  if (A->columns == B->rows) {
    for (int i = 0; i < result->columns; i++) {
      for (int j = 0; j < result->rows; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += (A->matrix[i][k] * B->matrix[k][j]);
        }
      }
    }
  } else {
    resulting_code = CALCULATION_ERROR;
  }
  return resulting_code;
}