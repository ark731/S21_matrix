#include <math.h>

#include "s21_matrix.h"
#include "s21_matrix_common.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  !err ? err = s21_matrix_is_valid(B) : 0;
  (!err && !result) ? err = 1 : 0;
  (!err && !s21_eq_matrix_size(A, B)) ? err = 2 : 0;
  !err ? err = s21_create_matrix((*A).rows, (*A).columns, result) : 0;
  if (err == 0) {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        *(*((*result).matrix + i) + j) =
            *(*((*A).matrix + i) + j) + *(*((*B).matrix + i) + j);
      }
    }
  }
  !err ? err = s21_matrix_is_valid(result) : 0;
  return err;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  !err ? err = s21_matrix_is_valid(B) : 0;
  (!err && !result) ? err = 1 : 0;
  (!err && !s21_eq_matrix_size(A, B)) ? err = 2 : 0;
  !err ? err = s21_create_matrix((*A).rows, (*A).columns, result) : 0;
  if (err == 0) {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        *(*((*result).matrix + i) + j) =
            *(*((*A).matrix + i) + j) - *(*((*B).matrix + i) + j);
      }
    }
  }
  !err ? err = s21_matrix_is_valid(result) : 0;
  return err;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  (!err && !result) ? err = 1 : 0;
  (!err && (isnan(number) || isinf(number))) ? err = 2 : 0;
  !err ? err = s21_create_matrix((*A).rows, (*A).columns, result) : 0;
  if (err == 0) {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        *(*((*result).matrix + i) + j) = *(*((*A).matrix + i) + j) * number;
      }
    }
  }
  !err ? err = s21_matrix_is_valid(result) : 0;
  return err;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  !err ? err = s21_matrix_is_valid(B) : 0;
  (!err && ((*A).columns != (*B).rows)) ? err = 2 : 0;
  !err ? err = s21_create_matrix((*A).rows, (*B).columns, result) : 0;
  if (!err) {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*B).columns; ++j) {
        for (int k = 0; k < (*A).columns; ++k) {
          *(*((*result).matrix + i) + j) +=
              *(*((*A).matrix + i) + k) * *(*((*B).matrix + k) + j);
        }
      }
    }
  }

  return err;
}