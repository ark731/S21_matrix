#include <stdlib.h>

#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int err = 0;
  if (!result) {
    err = 1;
  } else if (rows < 1 || columns < 1) {
    err = 1;
    (*result).rows = 0;
    (*result).columns = 0;
  } else {
    (*result).matrix = calloc(rows, sizeof(double *));
    if (!(*result).matrix) {
      err = 1;
    } else {
      for (int i = 0; i < rows; i++) {
        *((*result).matrix + i) = calloc(columns, sizeof(double));
        !(*((*result).matrix + i)) ? err = 1 : 0;
      }
      (*result).rows = rows;
      (*result).columns = columns;
    }
  }
  if (err) s21_remove_matrix(result);
  return err;
}

void s21_remove_matrix(matrix_t *A) {
  if (A) {
    if ((*A).matrix) {
      for (int i = 0; i < (*A).rows; i++) {
        if (*((*A).matrix + i)) {
          free(*((*A).matrix + i));
        }
      }
      free((*A).matrix);
    }
    (*A).rows = 0;
    (*A).columns = 0;
  }
}