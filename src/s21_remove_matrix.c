#include "s21_matrix.h"
void s21_remove_matrix(matrix_t *A) {
  if (A) {
    for (int i = 0; i < A->columns; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
    *A = s21_init_matrix();
  }
}