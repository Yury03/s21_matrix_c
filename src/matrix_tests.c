#include <check.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_matrix.h"

#define TRUE 1   // SUCCESS
#define FALSE 0  // FAILURE

// FUNCTIONS FOR TESTS
double generate_value_in_range(double min, double max) {
  double range = max - min;
  return min + (rand() / (RAND_MAX / range));
}

void fill_matrix_range(matrix_t *matrix, double minvalue, double maxvalue) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = generate_value_in_range(minvalue, maxvalue);
    }
  }
}

void fill_matrix_increment(matrix_t *matrix, int value) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      matrix->matrix[i][j] = value++;
    }
  }
}
void fill_matrix_increment2(matrix_t *matrix, int value) {
  for (int i = 0; i < matrix->rows; i++) {
    for (int j = 0; j < matrix->columns; j++) {
      // printf("value: %d\n", value);
      matrix->matrix[i][j] = value++;
    }
  }
}
// TESTS

// create

START_TEST(test_create_matrix_1) {
  matrix_t m0;

  ck_assert_int_eq(s21_create_matrix(2, 2, &m0), OK);
  ck_assert_ptr_ne(m0.matrix, NULL);

  matrix_t m = s21_init_matrix();

  ck_assert_int_eq(s21_create_matrix(m.rows, m.columns, &m), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(-100, -100, &m), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_create_matrix(20, 20, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m0);
  ck_assert_ptr_eq(m0.matrix, NULL);
}
END_TEST

START_TEST(test_create_matrix_2) {
  matrix_t m = s21_init_matrix();

  for (int i = 1; i < 100; i++) {
    int outv = s21_create_matrix(i, i, &m);
    ck_assert_int_eq(outv, OK);
    ck_assert_int_eq(m.rows, i);
    ck_assert_int_eq(m.columns, i);
    ck_assert_ptr_ne(m.matrix, NULL);
    ck_assert_int_eq(m.matrix[0][0], 0);

    s21_remove_matrix(&m);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
    ck_assert_ptr_eq(m.matrix, NULL);
  }
}
END_TEST
START_TEST(test_create_matrix_3) {
  matrix_t result;
  int rows = 2, columns = 10;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(0, exit_code);
}
END_TEST

START_TEST(test_create_matrix_4) {
  matrix_t result;
  int rows = 2, columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(0, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_matrix_5) {
  matrix_t result = {0};
  int rows = 0;
  int columns = 2;
  int exit_code = s21_create_matrix(rows, columns, &result);
  ck_assert_int_eq(1, exit_code);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_create_matrix_6) {
  matrix_t result = {0};
  int rows = 0, columns = 0;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(test_create_matrix_7) {
  matrix_t result = {0};
  int rows = 4, columns = -7;
  int exit_code = s21_create_matrix(rows, columns, &result);
  s21_remove_matrix(&result);
  ck_assert_int_eq(1, exit_code);
}
END_TEST

START_TEST(test_create_matrix_8) {
  ck_assert_int_eq(1, s21_create_matrix(0, 0, NULL));
}
END_TEST
// remove

START_TEST(test_remove_matrix_1) {
  matrix_t m = s21_init_matrix();
  s21_remove_matrix(NULL);

  s21_remove_matrix(&m);
  ck_assert_int_eq(m.rows, 0);
  ck_assert_int_eq(m.columns, 0);
  ck_assert_ptr_eq(m.matrix, NULL);

  s21_create_matrix(25, 36, &m);
  s21_remove_matrix(&m);
  ck_assert_int_eq(m.rows, 0);
  ck_assert_int_eq(m.columns, 0);
  ck_assert_ptr_eq(m.matrix, NULL);
}
END_TEST

START_TEST(test_remove_matrix_2) {
  matrix_t m = s21_init_matrix();

  for (int i = -50; i < 0; i++) {
    int outv = s21_create_matrix(i, i, &m);
    ck_assert_int_eq(outv, INCORRECT_MATRIX);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
    ck_assert_ptr_eq(m.matrix, NULL);

    s21_remove_matrix(&m);
    ck_assert_int_eq(m.rows, 0);
    ck_assert_int_eq(m.columns, 0);
    ck_assert_ptr_eq(m.matrix, NULL);
  }
}
END_TEST

// eq

START_TEST(test_eq_matrix_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    for (int j = 1; j < 20; j++) {
      s21_create_matrix(i, j, &m1);
      s21_create_matrix(j, i, &m2);

      if (i == j) {
        ck_assert_int_eq(s21_eq_matrix(&m1, &m2), TRUE);
      } else {
        ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FALSE);
      }

      s21_remove_matrix(&m1);
      s21_remove_matrix(&m2);
    }
  }
}
END_TEST

START_TEST(test_eq_matrix_2) {
  matrix_t m1 = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    s21_create_matrix(i, i, &m1);
    fill_matrix_range(&m1, -10.0, 10.0);
    ck_assert_int_eq(s21_eq_matrix(&m1, &m1), TRUE);
    s21_remove_matrix(&m1);
  }
}
END_TEST

START_TEST(test_eq_matrix_3) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    s21_create_matrix(i, i, &m1);
    s21_create_matrix(i, i, &m2);

    fill_matrix_increment(&m1, 23.0);
    fill_matrix_increment(&m2, 2.0);

    ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FALSE);

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
  }
}
END_TEST

START_TEST(test_eq_matrix_4) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();

  ck_assert_int_eq(s21_eq_matrix(&m1, &m2), FALSE);

  s21_create_matrix(10, 30, &m1);
  s21_create_matrix(10, 30, &m2);

  fill_matrix_increment(&m1, 23.0);
  fill_matrix_increment(&m2, 2.0);

  ck_assert_int_eq(s21_eq_matrix(&m1, NULL), FALSE);
  ck_assert_int_eq(s21_eq_matrix(NULL, &m2), FALSE);
  ck_assert_int_eq(s21_eq_matrix(NULL, NULL), FALSE);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

// sum matrix

START_TEST(test_sum_matrix_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(10, 30, &m1);
  s21_create_matrix(10, 30, &m2);

  fill_matrix_increment(&m1, 23.0);
  fill_matrix_increment(&m2, 2.0);

  ck_assert_int_eq(s21_sum_matrix(&m1, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(NULL, &m2, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(NULL, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sum_matrix(&m1, &m2, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(test_sum_matrix_2) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    for (int j = 1; j < 20; j++) {
      s21_create_matrix(i, j, &m1);
      s21_create_matrix(j, i, &m2);

      if (i == j) {
        ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_result), OK);
        s21_remove_matrix(&m_result);
      } else {
        ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_result),
                         CALCULATION_ERROR);
      }

      s21_remove_matrix(&m1);
      s21_remove_matrix(&m2);
    }
  }
}
END_TEST

START_TEST(test_sum_matrix_3) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    s21_create_matrix(i, i, &m1);
    s21_create_matrix(i, i, &m2);

    fill_matrix_increment(&m1, 23.0);
    fill_matrix_increment(&m2, 2.0);

    ck_assert_int_eq(s21_sum_matrix(&m1, &m2, &m_result), OK);

    for (int r = 0; r < m1.rows; r++) {
      for (int c = 0; c < m1.columns; c++) {
        ck_assert_int_eq(m_result.matrix[r][c],
                         m1.matrix[r][c] + m2.matrix[r][c]);
      }
    }

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&m_result);
  }
}
END_TEST
START_TEST(test_sum_matrix_4) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] + B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_5) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] + B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] + B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  int Arows = 5, Acolumns = 5;
  int Brows = 4, Bcolumns = 5;

  s21_create_matrix(Arows, Acolumns, &A);
  s21_create_matrix(Brows, Bcolumns, &B);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sum_matrix_8) {
  matrix_t A = {0}, B = {0}, result = {0};
  A.matrix = NULL, B.matrix = NULL;
  s21_create_matrix(0, 0, &result);
  ck_assert_int_eq(s21_sum_matrix(&A, &B, &result), 1);
}
END_TEST

// sub matrix

START_TEST(test_sub_matrix_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(10, 30, &m1);
  s21_create_matrix(10, 30, &m2);

  fill_matrix_increment(&m1, 23.0);
  fill_matrix_increment(&m2, 2.0);

  ck_assert_int_eq(s21_sub_matrix(&m1, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(NULL, &m2, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(NULL, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_sub_matrix(&m1, &m2, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(test_sub_matrix_2) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    for (int j = 1; j < 20; j++) {
      s21_create_matrix(i, j, &m1);
      s21_create_matrix(j, i, &m2);

      if (i == j) {
        ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_result), OK);
        s21_remove_matrix(&m_result);
      } else {
        ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_result),
                         CALCULATION_ERROR);
      }

      s21_remove_matrix(&m1);
      s21_remove_matrix(&m2);
    }
  }
}
END_TEST

START_TEST(test_sub_matrix_3) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    s21_create_matrix(i, i, &m1);
    s21_create_matrix(i, i, &m2);

    fill_matrix_range(&m1, 23.0, 70.0);
    fill_matrix_range(&m2, -10.0, 10.0);

    ck_assert_int_eq(s21_sub_matrix(&m1, &m2, &m_result), OK);

    for (int r = 0; r < m1.rows; r++) {
      for (int c = 0; c < m1.columns; c++) {
        ck_assert_int_eq(m_result.matrix[r][c],
                         m1.matrix[r][c] - m2.matrix[r][c]);
      }
    }

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m2);
    s21_remove_matrix(&m_result);
  }
}
END_TEST

START_TEST(test_sub_matrix_4) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_5) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_6) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_7) {
  matrix_t A = {0}, B = {0}, result = {0};
  int Arows = 5, Acolumns = 5;
  int Brows = 4, Bcolumns = 5;
  s21_create_matrix(Arows, Acolumns, &A);
  s21_create_matrix(Brows, Bcolumns, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_8) {
  matrix_t A = {0}, B = {0}, result = {0};
  A.matrix = NULL, B.matrix = NULL;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 1);
}
END_TEST
START_TEST(test_sub_matrix_9) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_10) {
  matrix_t A = {0}, B = {0}, result;
  A.matrix = NULL, B.matrix = NULL;
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_11) {
  matrix_t A = {0}, B = {0}, result = {0};
  int rows = 5, columns = 5;
  s21_create_matrix(rows, columns, &A);
  s21_create_matrix(rows, columns, &B);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
      B.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 0);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      ck_assert_double_eq_tol(A.matrix[i][j] - B.matrix[i][j],
                              result.matrix[i][j], 1e-8);
    }
  }
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_sub_matrix_12) {
  matrix_t A = {0}, B = {0}, result = {0};
  int Arows = 5, Acolumns = 5;
  int Brows = 4, Bcolumns = 5;
  s21_create_matrix(Arows, Acolumns, &A);
  s21_create_matrix(Brows, Bcolumns, &B);
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_5) {
  matrix_t A = {0}, B = {0}, result = {0};
  A.matrix = NULL, B.matrix = NULL;
  ck_assert_int_eq(s21_sub_matrix(&A, &B, &result), 1);
}
END_TEST
// mult matrix

START_TEST(test_mult_matrix_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(10, 30, &m1);
  s21_create_matrix(30, 10, &m2);

  fill_matrix_increment(&m1, 23.0);
  fill_matrix_increment(&m2, 2.0);

  ck_assert_int_eq(s21_mult_matrix(&m1, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(NULL, &m2, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(NULL, NULL, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(test_mult_matrix_2) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  s21_create_matrix(2, 2, &m1);
  fill_matrix_increment(&m1, 1);

  s21_create_matrix(2, 2, &m2);
  fill_matrix_increment(&m2, 1);

  int result = s21_mult_matrix(&m1, &m2, &m_result);

  ck_assert_int_eq(m_result.matrix[0][0], 7);
  ck_assert_int_eq(m_result.matrix[0][1], 10);
  ck_assert_int_eq(m_result.matrix[1][0], 15);
  ck_assert_int_eq(m_result.matrix[1][1], 22);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m_result);
}
END_TEST

START_TEST(test_mult_matrix_3) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  s21_create_matrix(10, 30, &m1);
  s21_create_matrix(10, 30, &m2);

  ck_assert_int_eq(s21_mult_matrix(&m1, &m2, &m_result), CALCULATION_ERROR);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m2);
  s21_remove_matrix(&m_result);
}
END_TEST

// mult number

START_TEST(test_mult_number_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_mult_number(&m1, 111.34, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(10, 30, &m1);
  fill_matrix_increment(&m1, 23.0);

  ck_assert_int_eq(s21_mult_number(&m1, 2, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_number(NULL, 4, &m1), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_mult_number(NULL, -45, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
}
END_TEST

START_TEST(test_mult_number_2) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  for (int i = 1; i < 20; i++) {
    s21_create_matrix(i, i, &m1);

    double numb = i - 10;
    fill_matrix_range(&m1, -10.0, 70.0);

    ck_assert_int_eq(s21_mult_number(&m1, numb, &m_result), OK);

    for (int r = 0; r < m1.rows; r++) {
      for (int c = 0; c < m1.columns; c++) {
        ck_assert_int_eq(m_result.matrix[r][c], m1.matrix[r][c] * numb);
      }
    }

    s21_remove_matrix(&m1);
    s21_remove_matrix(&m_result);
  }
}
END_TEST

// transpose

START_TEST(test_transpose_1) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_transpose(&m1, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(10, 30, &m1);
  fill_matrix_increment(&m1, 23.0);

  ck_assert_int_eq(s21_transpose(&m1, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_transpose(NULL, &m1), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_transpose(NULL, NULL), INCORRECT_MATRIX);

  s21_remove_matrix(&m1);
}
END_TEST

void print_matrix(matrix_t *m) {
  for (int i = 0; i < m->rows; i++) {
    for (int j = 0; j < m->columns; j++) {
      printf("%f  ", m->matrix[i][j]);
    }
    printf("\n");
  }
}
START_TEST(test_transpose_2) {
  matrix_t m1 = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  s21_create_matrix(2, 3, &m1);
  fill_matrix_increment2(&m1, 1);
  // print_matrix(&m1);
  int result = s21_transpose(&m1, &m_result);
  // print_matrix(&m1);
  // print_matrix(&m_result);
  ck_assert_int_eq((int)m_result.matrix[0][0], 1);
  ck_assert_int_eq((int)m_result.matrix[0][1], 4);
  ck_assert_int_eq((int)m_result.matrix[1][0], 2);
  ck_assert_int_eq((int)m_result.matrix[1][1], 5);
  ck_assert_int_eq((int)m_result.matrix[2][0], 3);
  ck_assert_int_eq((int)m_result.matrix[2][1], 6);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&m1);
  s21_remove_matrix(&m_result);
}
END_TEST

START_TEST(test_transpose_3) {
  matrix_t A = {0}, result;
  int rows = 3, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_4) {
  matrix_t A = {0}, result;
  int rows = 31, columns = 52;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_5) {
  matrix_t A = {0}, result = {0};
  int rows = 51, columns = 5;
  s21_create_matrix(rows, columns, &A);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      A.matrix[i][j] = (double)(rand()) / RAND_MAX;
    }
  }
  ck_assert_int_eq(s21_transpose(&A, &result), 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_transpose_6) {
  matrix_t A = {0}, result = {0};
  A.matrix = NULL;
  ck_assert_int_eq(s21_transpose(&A, &result), 1);
}
END_TEST

START_TEST(test_transpose_7) {
  matrix_t A = {0}, result = {0}, result_tmp = {0};
  int rows = 3, columns = 2;
  int sum = 0;
  s21_create_matrix(rows, columns, &A);
  A.matrix[0][0] = 1;
  A.matrix[0][1] = 4;
  A.matrix[1][0] = 2;
  A.matrix[1][1] = 5;
  A.matrix[2][0] = 3;
  A.matrix[2][1] = 6;
  s21_create_matrix(columns, rows, &result_tmp);
  result_tmp.matrix[0][0] = 1;
  result_tmp.matrix[0][1] = 2;
  result_tmp.matrix[0][2] = 3;
  result_tmp.matrix[1][0] = 4;
  result_tmp.matrix[1][1] = 5;
  result_tmp.matrix[1][2] = 6;
  s21_transpose(&A, &result);
  for (int i = 0; i < columns; i++) {
    for (int j = 0; j < rows; j++) {
      if (fabs(result_tmp.matrix[i][j] - result.matrix[i][j]) > 1e-8) {
        sum++;
      }
    }
  }
  ck_assert_int_eq(sum, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
  s21_remove_matrix(&result_tmp);
}
END_TEST
START_TEST(test_transpose_8) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);

  matrix_t check = {0};
  s21_create_matrix(cols, rows, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      // double rand_val = (i + j - rand()) / 21;
      double rand_val = 4.235;
      m.matrix[i][j] = rand_val;
      check.matrix[j][i] = rand_val;
    }
  }

  matrix_t res = {0};

  ck_assert_int_eq(s21_transpose(&m, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST
// calc complements

START_TEST(test_calc_complements_1) {
  matrix_t m = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 3;
  m.matrix[1][0] = 0;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  int result = s21_calc_complements(&m, &m_result);

  ck_assert_int_eq(m_result.matrix[0][0], 0);
  ck_assert_int_eq(m_result.matrix[0][1], 10);
  ck_assert_int_eq(m_result.matrix[0][2], -20);
  ck_assert_int_eq(m_result.matrix[1][0], 4);
  ck_assert_int_eq(m_result.matrix[1][1], -14);
  ck_assert_int_eq(m_result.matrix[1][2], 8);
  ck_assert_int_eq(m_result.matrix[2][0], -8);
  ck_assert_int_eq(m_result.matrix[2][1], -2);
  ck_assert_int_eq(m_result.matrix[2][2], 4);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_result);
}
END_TEST

START_TEST(test_calc_complements_2) {
  matrix_t m = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_calc_complements(&m, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(NULL, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_calc_complements(NULL, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(3, 3, &m);

  ck_assert_int_eq(s21_calc_complements(&m, &m_result), OK);

  m.columns = 1;
  ck_assert_int_eq(s21_calc_complements(&m, &m_result), CALCULATION_ERROR);
  s21_remove_matrix(&m_result);

  m.rows = 0;
  m.columns = 0;
  ck_assert_int_eq(s21_calc_complements(&m, &m_result), INCORRECT_MATRIX);

  m.rows = 3;
  m.columns = 3;
  s21_remove_matrix(&m);
  s21_remove_matrix(&m_result);
}
END_TEST

// determinant

START_TEST(test_determinant_1) {
  double determinant = 0;
  matrix_t m = s21_init_matrix();

  s21_create_matrix(3, 3, &m);
  fill_matrix_increment(&m, 1);

  int result = s21_determinant(&m, &determinant);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_determinant_2) {
  double determinant = 0;
  matrix_t m = s21_init_matrix();
  matrix_t m2 = s21_init_matrix();

  s21_create_matrix(4, 4, &m);
  s21_create_matrix(1, 1, &m2);

  m.matrix[0][0] = 9;
  m.matrix[0][1] = 2;
  m.matrix[0][2] = 2;
  m.matrix[0][3] = 4;

  m.matrix[1][0] = 3;
  m.matrix[1][1] = 4;
  m.matrix[1][2] = 4;
  m.matrix[1][3] = 4;

  m.matrix[2][0] = 4;
  m.matrix[2][1] = 4;
  m.matrix[2][2] = 9;
  m.matrix[2][3] = 9;

  m.matrix[3][0] = 1;
  m.matrix[3][1] = 1;
  m.matrix[3][2] = 5;
  m.matrix[3][3] = 1;

  int result = s21_determinant(&m, &determinant);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(determinant, -578);

  m2.matrix[0][0] = 10;
  result = s21_determinant(&m2, &determinant);

  ck_assert_int_eq(result, OK);
  ck_assert_int_eq(determinant, 10);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m2);
}
END_TEST

START_TEST(test_determinant_3) {
  matrix_t m = s21_init_matrix();
  double determinant = 0;

  ck_assert_int_eq(s21_determinant(NULL, &determinant), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_determinant(NULL, NULL), INCORRECT_MATRIX);

  s21_create_matrix(2, 2, &m);
  ck_assert_int_eq(s21_determinant(&m, NULL), INCORRECT_MATRIX);
  s21_remove_matrix(&m);

  s21_create_matrix(4, 2, &m);
  ck_assert_int_eq(s21_determinant(&m, &determinant), CALCULATION_ERROR);
  s21_remove_matrix(&m);

  s21_create_matrix(2, 0, &m);
  ck_assert_int_eq(s21_determinant(&m, &determinant), INCORRECT_MATRIX);
  s21_remove_matrix(&m);
}
END_TEST

// inverse

START_TEST(test_inverse_matrix_1) {
  matrix_t m = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 4;
  m.matrix[0][1] = -2;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 1;
  m.matrix[1][1] = 6;
  m.matrix[1][2] = -2;
  m.matrix[2][0] = 1;
  m.matrix[2][1] = 0;
  m.matrix[2][2] = 0;

  int result = s21_inverse_matrix(&m, &m_result);

  ck_assert_int_eq(m_result.matrix[0][1], 0);
  ck_assert_int_eq(m_result.matrix[0][2], 1);
  ck_assert_int_eq(m_result.matrix[1][0], 1);
  ck_assert_int_eq(m_result.matrix[2][0], 3);
  ck_assert_int_eq(m_result.matrix[2][1], 1);
  ck_assert_int_eq(m_result.matrix[2][2], -13);
  ck_assert_int_eq(result, OK);

  s21_remove_matrix(&m);
  s21_remove_matrix(&m_result);
}
END_TEST

START_TEST(test_inverse_matrix_2) {
  matrix_t m = s21_init_matrix();
  matrix_t m_result = s21_init_matrix();

  ck_assert_int_eq(s21_inverse_matrix(NULL, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(&m, NULL), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(&m, &m_result), INCORRECT_MATRIX);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &m_result), INCORRECT_MATRIX);

  s21_create_matrix(3, 3, &m);

  m.matrix[0][0] = 1;
  m.matrix[0][1] = 4;
  m.matrix[0][2] = 1;
  m.matrix[1][0] = 3;
  m.matrix[1][1] = 7;
  m.matrix[1][2] = 2;
  m.matrix[2][0] = 3;
  m.matrix[2][1] = 2;
  m.matrix[2][2] = 1;

  double determinant = 0;
  s21_determinant(&m, &determinant);
  ck_assert_int_lt(determinant, 1);

  ck_assert_int_eq(s21_inverse_matrix(&m, &m_result), CALCULATION_ERROR);
  s21_remove_matrix(&m_result);

  m.rows = 0;
  s21_create_matrix(3, 3, &m_result);
  ck_assert_int_eq(s21_inverse_matrix(&m, &m_result), INCORRECT_MATRIX);

  m.rows = 3;
  s21_remove_matrix(&m);
  s21_remove_matrix(&m_result);
}
END_TEST

// SUITES

Suite *suite_create_matrix() {
  Suite *s = suite_create("suite_create_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");
  TCase *tc_4 = tcase_create("tc_4");
  TCase *tc_5 = tcase_create("tc_5");
  TCase *tc_6 = tcase_create("tc_6");
  TCase *tc_7 = tcase_create("tc_7");

  tcase_add_test(tc_1, test_create_matrix_1);
  tcase_add_test(tc_2, test_create_matrix_2);
  tcase_add_test(tc_3, test_create_matrix_3);
  tcase_add_test(tc_4, test_create_matrix_4);
  tcase_add_test(tc_5, test_create_matrix_5);
  tcase_add_test(tc_6, test_create_matrix_6);
  tcase_add_test(tc_6, test_create_matrix_7);
  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);
  suite_add_tcase(s, tc_4);
  suite_add_tcase(s, tc_5);
  suite_add_tcase(s, tc_6);
  suite_add_tcase(s, tc_7);

  return s;
}

Suite *suite_remove_matrix() {
  Suite *s = suite_create("suite_remove_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");

  tcase_add_test(tc_1, test_remove_matrix_1);
  tcase_add_test(tc_2, test_remove_matrix_2);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);

  return s;
}

Suite *suite_eq_matrix() {
  Suite *s = suite_create("suite_eq_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");
  TCase *tc_4 = tcase_create("tc_4");

  tcase_add_test(tc_1, test_eq_matrix_1);
  tcase_add_test(tc_2, test_eq_matrix_2);
  tcase_add_test(tc_3, test_eq_matrix_3);
  tcase_add_test(tc_4, test_eq_matrix_4);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);
  suite_add_tcase(s, tc_4);

  return s;
}

Suite *suite_sum_matrix() {
  Suite *s = suite_create("suite_sum_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");
  TCase *tc_4 = tcase_create("tc_3");
  tcase_add_test(tc_1, test_sum_matrix_1);
  tcase_add_test(tc_2, test_sum_matrix_2);
  tcase_add_test(tc_3, test_sum_matrix_3);
  tcase_add_test(tc_4, test_sum_matrix_4);
  tcase_add_test(tc_4, test_sum_matrix_5);
  tcase_add_test(tc_4, test_sum_matrix_6);
  tcase_add_test(tc_4, test_sum_matrix_7);
  tcase_add_test(tc_4, test_sum_matrix_8);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);
  suite_add_tcase(s, tc_4);

  return s;
}

Suite *suite_sub_matrix() {
  Suite *s = suite_create("suite_sub_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");
  TCase *tc_4 = tcase_create("tc_4");
  tcase_add_test(tc_1, test_sub_matrix_1);
  tcase_add_test(tc_2, test_sub_matrix_2);
  tcase_add_test(tc_3, test_sub_matrix_3);
  tcase_add_test(tc_4, test_sub_matrix_4);
  tcase_add_test(tc_4, test_sub_matrix_5);
  tcase_add_test(tc_4, test_sub_matrix_6);
  tcase_add_test(tc_4, test_sub_matrix_7);
  tcase_add_test(tc_4, test_sub_matrix_8);
  tcase_add_test(tc_4, test_sub_matrix_9);
  tcase_add_test(tc_4, test_sub_matrix_10);
  tcase_add_test(tc_4, test_sub_matrix_11);
  tcase_add_test(tc_4, test_sub_matrix_12);
  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);
  suite_add_tcase(s, tc_4);

  return s;
}

Suite *suite_mult_matrix() {
  Suite *s = suite_create("suite_mult_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");

  tcase_add_test(tc_1, test_mult_matrix_1);
  tcase_add_test(tc_2, test_mult_matrix_2);
  tcase_add_test(tc_3, test_mult_matrix_3);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);

  return s;
}

Suite *suite_mult_number() {
  Suite *s = suite_create("suite_mult_number");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");

  tcase_add_test(tc_1, test_mult_number_1);
  tcase_add_test(tc_2, test_mult_number_2);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);

  return s;
}

Suite *suite_transpose() {
  Suite *s = suite_create("suite_transpose");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");

  tcase_add_test(tc_1, test_transpose_1);
  tcase_add_test(tc_2, test_transpose_2);
  tcase_add_test(tc_3, test_transpose_3);
  tcase_add_test(tc_3, test_transpose_4);
  tcase_add_test(tc_3, test_transpose_5);
  tcase_add_test(tc_3, test_transpose_6);
  tcase_add_test(tc_3, test_transpose_7);
  tcase_add_test(tc_3, test_transpose_8);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);

  return s;
}

Suite *suite_calc_complements() {
  Suite *s = suite_create("suite_calc_complements");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");

  tcase_add_test(tc_1, test_calc_complements_1);
  tcase_add_test(tc_2, test_calc_complements_2);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);

  return s;
}

Suite *suite_determinant() {
  Suite *s = suite_create("suite_determinant");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");
  TCase *tc_3 = tcase_create("tc_3");

  tcase_add_test(tc_1, test_determinant_1);
  tcase_add_test(tc_2, test_determinant_2);
  tcase_add_test(tc_3, test_determinant_3);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);
  suite_add_tcase(s, tc_3);

  return s;
}

Suite *suite_inverse_matrix() {
  Suite *s = suite_create("suite_inverse_matrix");
  TCase *tc_1 = tcase_create("tc_1");
  TCase *tc_2 = tcase_create("tc_2");

  tcase_add_test(tc_1, test_inverse_matrix_1);
  tcase_add_test(tc_2, test_inverse_matrix_2);

  suite_add_tcase(s, tc_1);
  suite_add_tcase(s, tc_2);

  return s;
}

// MAIN

void run_test(Suite *thesuit) {
  SRunner *therunner = srunner_create(thesuit);

  srunner_set_fork_status(therunner, CK_NOFORK);
  srunner_run_all(therunner, CK_NORMAL);
  srunner_ntests_failed(therunner);
  srunner_free(therunner);

  printf("\n");
}

int main() {
  printf("\n");
  srand(time(NULL));

  Suite *s_create_matrix = suite_create_matrix();
  Suite *s_remove_matrix = suite_remove_matrix();
  Suite *s_eq_matrix = suite_eq_matrix();
  Suite *s_sum_matrix = suite_sum_matrix();
  Suite *s_sub_matrix = suite_sub_matrix();
  Suite *s_mult_matrix = suite_mult_matrix();
  Suite *s_mult_number = suite_mult_number();
  Suite *s_transpose = suite_transpose();
  Suite *s_calc_complements = suite_calc_complements();
  Suite *s_determinant = suite_determinant();
  Suite *s_inverse_matrix = suite_inverse_matrix();

  run_test(s_create_matrix);
  run_test(s_remove_matrix);
  run_test(s_eq_matrix);
  run_test(s_sum_matrix);
  run_test(s_sub_matrix);
  run_test(s_mult_matrix);
  run_test(s_mult_number);
  run_test(s_transpose);
  run_test(s_calc_complements);
  run_test(s_determinant);
  run_test(s_inverse_matrix);

  return 0;
}