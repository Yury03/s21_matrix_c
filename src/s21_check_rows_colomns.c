#include "s21_matrix.h"
int s21_check_rows_columns(matrix_t *A, matrix_t *B) {
  return (A->columns != B->columns || A->rows != B->rows) ? CALCULATION_ERROR
                                                          : OK;
}