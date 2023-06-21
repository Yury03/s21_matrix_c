#include "s21_matrix.h"
int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int errorState = OK;
  if (s21_null_check(A) != OK || !result) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;
  double determinant;
  s21_determinant(A, &determinant);
  if (determinant != 0) {
    matrix_t compl = s21_init_matrix();
    s21_calc_complements(A, &compl );
    matrix_t complTransp = s21_init_matrix();
    s21_transpose(&compl, &complTransp);
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = complTransp.matrix[i][j] / determinant;
      }
    }
    s21_remove_matrix(&compl );
    s21_remove_matrix(&complTransp);
  } else {
    errorState = CALCULATION_ERROR;
  }

  return errorState;
}