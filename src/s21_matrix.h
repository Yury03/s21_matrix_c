#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);     // readme
void s21_remove_matrix(matrix_t *A);                                // readme
matrix_t s21_init_matrix();                                         // helper
int s21_eq_matrix(matrix_t *A, matrix_t *B);                        // readme
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // readme
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);     // readme
int s21_mult_number(matrix_t *A, double number, matrix_t *result);  // readme
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);    // readme
int s21_null_check(matrix_t *A);                                    // helper
int s21_check_rows_columns(matrix_t *A, matrix_t *B);               // helper
int s21_transpose(matrix_t *A, matrix_t *result);                   // readme
int s21_calc_complements(matrix_t *A, matrix_t *result);            // readme
int s21_determinant(matrix_t *A, double *result);                   // readme
int s21_inverse_matrix(matrix_t *A, matrix_t *result);              // readme

#endif  // SRC_S21_MATRIX_H_
