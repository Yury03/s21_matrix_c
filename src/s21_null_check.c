#include "s21_matrix.h"
int s21_null_check(matrix_t *A) {
  return (A && A->matrix != NULL && A->columns > 0 && A->rows > 0)
             ? OK
             : INCORRECT_MATRIX;
}
