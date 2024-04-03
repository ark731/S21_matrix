#include "s21_matrix_common.h"

#include "s21_matrix.h"

#define SUCCESS 1
#define FAILURE 0

int s21_matrix_is_valid(matrix_t *A) {
  int err = 1;
  if (A && (*A).matrix && (*A).rows > 0 && (*A).columns > 0) {
    err = 0;
    for (int i = 0; i < (*A).rows; ++i) {
      if ((*A).matrix) {
        for (int j = 0; j < (*A).columns; ++j) {
          (isnan(*(*((*A).matrix + i) + j)) || isinf(*(*((*A).matrix + i) + j)))
              ? err = 2
              : 0;
        }
      } else {
        err = 1;
        i = (*A).rows;
      }
    }
  }
  return err;
}

int s21_eq_matrix_size(matrix_t *A, matrix_t *B) {
  int err = FAILURE;
  if (A && B && (*A).rows == (*B).rows && (*A).columns == (*B).columns) {
    err = SUCCESS;
  }
  return err;
}

int s21_matrix_minor(matrix_t *A, matrix_t *minor, int skip_row, int skip_col) {
  int err = s21_matrix_is_valid(A);
  !err ? err = s21_create_matrix((*A).rows - 1, (*A).columns - 1, minor) : 0;
  if (!err) {
    for (int i = 0, m = 0; m < (*minor).rows; ++i, ++m) {
      (i == skip_row) ? ++i : 0;
      for (int j = 0, n = 0; n < (*minor).columns; ++j, ++n) {
        (j == skip_col) ? ++j : 0;
        *(*((*minor).matrix + m) + n) = *(*((*A).matrix + i) + j);
      }
    }
  }
  return err;
}

int s21_calc_single_complement(matrix_t *A, matrix_t *res, int row, int col) {
  matrix_t minor;
  int err = s21_matrix_minor(A, &minor, row, col);
  if (!err) {
    err = s21_determinant(&minor, &(*(*((*res).matrix + row) + col)));
    (!err && ((row + col) % 2))
        ? *(*((*res).matrix + row) + col) = -*(*((*res).matrix + row) + col)
        : 0;
    s21_remove_matrix(&minor);
  }
  return err;
}