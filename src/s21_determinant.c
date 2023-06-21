#include "s21_matrix.h"
int s21_determinant(matrix_t *A, double *result) {
  int resulting_code = 0;
  if (s21_null_check(A) != OK || !result) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;
  *result = 0.0;
  if (A->columns == 1) {
    *result = A->matrix[0][0];
  } else {
    for (int k = 0; k < A->rows; k++) {
      matrix_t temp = s21_init_matrix();
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      for (int i = 0; i < temp.columns; i++) {
        int n = 0;
        for (int j = 0; j < temp.rows; j++, n++) {
          if (j == k) n++;
          temp.matrix[i][j] = A->matrix[i + 1][n];
        }
      }
      double temp_result = 0.0;
      s21_determinant(&temp, &temp_result);
      *result += pow(-1.0, k) * A->matrix[0][k] * temp_result;
      s21_remove_matrix(&temp);
    }
  }
  return resulting_code;
}