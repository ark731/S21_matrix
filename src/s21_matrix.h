#ifndef S21_MATRIX
#define S21_MATRIX

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

/////////////////////////////////////////////////////////////////
/* ----------------- CONSTRUCTOR/DESTRUCTOR ------------------ */
/////////////////////////////////////////////////////////////////
/* Constructor. Returns:
 * 0 - OK
 * 1 - ERROR */
int s21_create_matrix(int rows, int columns, matrix_t *result);

/* Destructor. */
void s21_remove_matrix(matrix_t *A);

/////////////////////////////////////////////////////////////////
/* ------------------- MATRIX ARITHMETICS -------------------- */
/////////////////////////////////////////////////////////////////
/* Matrix addition. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Matrix substraction. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/* Matrix scalar multiplication. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_mult_number(matrix_t *A, double number, matrix_t *result);

/* Matrix multiplication. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

/////////////////////////////////////////////////////////////////
/* --------------------- LINEAR ALGEBRA ---------------------- */
/////////////////////////////////////////////////////////////////
/* Transpose matrix. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_transpose(matrix_t *A, matrix_t *result);

/* Build matrix of algebraic complements. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_calc_complements(matrix_t *A, matrix_t *result);

/* Find determinant. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_determinant(matrix_t *A, double *result);

/* Build inverse matrix. Returns:
 * 0 - OK
 * 1 - Incorrect matrix
 * 2 - Calculation error */
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

/////////////////////////////////////////////////////////////////
/* ------------------------- OTHER --------------------------- */
/////////////////////////////////////////////////////////////////
/* Check if matrices are equal to 7th decimal place. Returns:
 * 0 - NOT EQUAL
 * 1 - EQUAL */
int s21_eq_matrix(matrix_t *A, matrix_t *B);

#endif