#ifndef S21_MATRIX_COMMON
#define S21_MATRIX_COMMON

#include "s21_matrix.h"

int s21_matrix_is_valid(matrix_t *A);
int s21_eq_matrix_size(matrix_t *A, matrix_t *B);
int s21_matrix_minor(matrix_t *A, matrix_t *minor, int skip_row, int skip_col);
int s21_calc_single_complement(matrix_t *A, matrix_t *res, int row, int col);

#endif