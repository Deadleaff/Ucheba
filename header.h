#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

bool is_equal(double a, double b, double eps);
int choose_main_element(int* indi, double* a, int n, int i, double eps);
int jordan_algorithm(double* a, int* indi, double* b, double** x, int n, double eps);
void make_matrix(double *a, int n, int s);
void find_error_rate(double *r, int n, double* x, double *b, int s, double *a);
