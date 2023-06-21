#include "s21_matrix.h"
matrix_t s21_init_matrix() {
  matrix_t new_matrix;
  new_matrix.columns = 0;
  new_matrix.rows = 0;
  new_matrix.matrix = NULL;
  return new_matrix;
}
