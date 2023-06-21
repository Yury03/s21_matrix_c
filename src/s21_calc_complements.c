#include "s21_matrix.h"
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  if (s21_null_check(A) || !result) return INCORRECT_MATRIX;
  if (A->columns != A->rows) return CALCULATION_ERROR;
  s21_create_matrix(A->rows, A->columns, result);
  for (int i = 0; i < A->columns; i++) {
    for (int j = 0; j < A->rows; j++) {
      matrix_t temp = s21_init_matrix();
      s21_create_matrix(A->rows - 1, A->columns - 1, &temp);
      int columnСounter = 0;
      for (int k = 0; k < temp.columns; k++, columnСounter++) {
        if (k == i) columnСounter++;
        int rowsCounter = 0;
        for (int l = 0; l < temp.rows; l++, rowsCounter++) {
          if (l == j) rowsCounter++;
          temp.matrix[k][l] = A->matrix[columnСounter][rowsCounter];
        }
      }
      double minor = 0.0;
      s21_determinant(&temp, &minor);
      result->matrix[i][j] = pow(-1.0, i + j) * minor;
      s21_remove_matrix(&temp);
    }
  }
  return OK;
}

// int main()
// {
//   matrix_t m = s21_init_matrix();
//   matrix_t m_result = s21_init_matrix();

//   s21_create_matrix(3, 3, &m);

//   m.matrix[0][0] = 1;
//   m.matrix[0][1] = 2;
//   m.matrix[0][2] = 3;
//   m.matrix[1][0] = 0;
//   m.matrix[1][1] = 4;
//   m.matrix[1][2] = 2;
//   m.matrix[2][0] = 5;
//   m.matrix[2][1] = 2;
//   m.matrix[2][2] = 1;

//   int result = s21_calc_complements(&m, &m_result);
//   printf("%f\t%d\n", m_result.matrix[0][0], 0);
//   printf("%f\t%d\n", m_result.matrix[0][1], 10);
//   printf("%f\t%d\n", m_result.matrix[0][2], -20);
//   printf("%f\t%d\n", m_result.matrix[1][0], 4);
//   printf("%f\t%d\n", m_result.matrix[1][1], -14);
//   printf("%f\t%d\n", m_result.matrix[1][2], 8);
//   printf("%f\t%d\n", m_result.matrix[2][0], -8);
//   printf("%f\t%d\n", m_result.matrix[2][1], -2);
//   printf("%f\t%d\n", m_result.matrix[2][2], 4);

//   printf("%d\t%d\n", result, OK);

//   s21_remove_matrix(&m);
//   s21_remove_matrix(&m_result);
//   return 0;
// }