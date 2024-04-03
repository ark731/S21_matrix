#include <math.h>

#include "s21_matrix.h"
#include "s21_matrix_common.h"

#define SUCCESS 1
#define FAILURE 0

#ifndef S21_EPS
#define S21_EPS (0.0000001)
#endif

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = FAILURE;
  if (A && B && (*A).rows && (*A).rows == (*B).rows &&
      (*A).columns == (*B).columns) {
    err = SUCCESS;
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        if (fabs(*(*((*A).matrix + i) + j) - *(*((*B).matrix + i) + j)) >=
            S21_EPS) {
          err = FAILURE;
          i = (*A).rows;
          j = (*A).columns;
        }
      }
    }
  }
  return err;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  (!err && result) ? err = s21_create_matrix((*A).columns, (*A).rows, result)
                   : (err = 1);
  if (!err) {
    for (int i = 0; i < (*A).rows; ++i) {
      for (int j = 0; j < (*A).columns; ++j) {
        *(*((*result).matrix + j) + i) = *(*((*A).matrix + i) + j);
      }
    }
  }
  return err;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  (!err && (*A).rows != (*A).columns) ? err = 2 : 0;
  (!err && result) ? err = s21_create_matrix((*A).rows, (*A).columns, result)
                   : (err = 1);
  if (!err) {
    for (int i = 0; i < (*A).rows && !err; ++i) {
      for (int j = 0; j < (*A).columns && !err; ++j) {
        err = s21_calc_single_complement(A, result, i, j);
      }
    }
  }
  return err;
}

int s21_determinant(matrix_t *A, double *result) {
  int err = s21_matrix_is_valid(A);
  (!err && (*A).rows != (*A).columns) ? err = 2 : 0;
  if ((*A).rows == 1) {
    *result = **(*A).matrix;
  } else if ((*A).rows == 2) {
    *result = **(*A).matrix * *(*((*A).matrix + 1) + 1) -
              *(*(*A).matrix + 1) * **((*A).matrix + 1);
  } else if ((*A).rows == 3) {
    *result =
        **(*A).matrix * *(*((*A).matrix + 1) + 1) * *(*((*A).matrix + 2) + 2) -
        *(*(*A).matrix + 2) * *(*((*A).matrix + 1) + 1) * **((*A).matrix + 2) +
        *(*(*A).matrix + 1) * *(*((*A).matrix + 1) + 2) * **((*A).matrix + 2) +
        *(*(*A).matrix + 2) * *(*((*A).matrix + 2) + 1) * **((*A).matrix + 1) -
        **(*A).matrix * *(*((*A).matrix + 1) + 2) * *(*((*A).matrix + 2) + 1) -
        *(*(*A).matrix + 1) * *(*((*A).matrix + 2) + 2) * **((*A).matrix + 1);
  } else {
    *result = 0;
    for (int j = 0; j < (*A).columns && !err; ++j) {
      matrix_t minor;
      double tmp;
      err = s21_matrix_minor(A, &minor, 0, j);
      if (!err) {
        err = s21_determinant(&minor, &tmp);
        !err ? *result += *(*(*A).matrix + j) * tmp * (j % 2 ? -1 : 0) : 0;
        s21_remove_matrix(&minor);
      }
    }
  }
  return err;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int err = s21_matrix_is_valid(A);
  (!err && (*A).rows != (*A).columns) ? err = 2 : 0;
  if (!err) {
    double det;
    err = s21_determinant(A, &det);
    (det == 0.) ? err = 2 : 0;
    !err ? err = s21_create_matrix((*A).rows, (*A).columns, result) : 0;
    if (!err && (*A).rows == 1) {
      **(*result).matrix = 1.0 / det;
    } else if (!err) {
      matrix_t tmp, tmp2;
      err = s21_calc_complements(A, &tmp);
      if (!err) {
        s21_transpose(&tmp, &tmp2);
        err = s21_mult_number(&tmp2, 1 / det, result);
        s21_remove_matrix(&tmp);
        s21_remove_matrix(&tmp2);
      }
    }
  }
  return err;
}