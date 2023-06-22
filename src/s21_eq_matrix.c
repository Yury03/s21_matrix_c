#include "s21_matrix.h"
int compareDoubles(double a, double b) {
  return fabs(a - b) < 0.0000001 ? SUCCESS : FAILURE;
}
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int result = FAILURE;
  if (s21_null_check(A) != OK || s21_null_check(B) != OK) return FAILURE;
  if (A == B) return SUCCESS;
  if (A->columns == B->columns && A->rows == B->rows) {
    int isEquals = SUCCESS;
    for (int i = 0; i < A->rows && isEquals; i++)
      for (int j = 0; j < A->columns && isEquals; j++)
        isEquals = compareDoubles(A->matrix[i][j], B->matrix[i][j]);
    result = isEquals;
  }
  return result;
}