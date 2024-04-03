#ifndef S21_MATRIX_COMMON
#define S21_MATRIX_COMMON

#include "s21_matrix.h"

/* Checks validity of matrix_t structure. Checks all internal pointers for NULL,
 * checks rows and columns ( > 0), checks each cell for NAN or INF. Returns:
 * 0 - Valid matrix
 * 1 - Invalid matrix
 * 2 - NAN or INF in a cell */
int s21_matrix_is_valid(matrix_t *A);

/* Checks if matrices are of equal size. Returns:
 * 0 - Not equal size
 * 1 - Equal size */
int s21_eq_matrix_size(matrix_t *A, matrix_t *B);

/* Builds minor matrix. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_matrix_minor(matrix_t *A, matrix_t *minor, int skip_row, int skip_col);

/* Calculates algebraic complement matrix for given cell. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_calc_single_complement(matrix_t *A, matrix_t *res, int row, int col);

#endif