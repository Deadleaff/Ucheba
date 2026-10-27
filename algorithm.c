#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "header.h"

static int max(int i, int j) {
    return (i > j) ? i : j;
}

bool is_equal(double a, double b, double eps) {
    if(fabs(a - b) < eps) { return true;}
    else { return false;}
}

void swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int choose_main_element(int* indi, double* a, int n, int i, double eps) {
    double max = fabs(a[n*i + i]);
    int max_ind = i;
    for(int j = i + 1; j < n; j++) {

        if(fabs(a[n*i + j]) > max) {
            max = fabs(a[n*i + j]);
            max_ind = j;
        }     
    }
    if(is_equal(max, 0, eps)) {
        printf("Нельзя применить метод, матрица вырождена\n");
        return 1;
    }
    
    swap(indi + i, indi + max_ind);

    return 0;
}

int jordan_algorithm(double* a, int* indi, double* b, double* x, int n, double eps) {
    double factor;
    double main_elem;
    for(int i = 0; i < n; i++) {
        indi[i] = i;
    }

    for(int k = 0; k < n; k++) {

        if(is_equal(a[n*k + indi[k]], 0, eps)) {

            if(choose_main_element(indi, a, n, k, eps) != 0) {
                return 1;
            }
        }

        
        main_elem = a[n*k + indi[k]]; // Сохраняем главный элемент
        for(int j = k; j < n; j++) {
            a[n*k + indi[j]] /= main_elem;  // Делим на сохраненное значение
        }
        b[k] /= main_elem;

        for(int i = 0; i < n; i++) {
            if(i != k) {
                factor = a[i*n + indi[k]];
                for(int j = k; j < n; j++) {
                    a[i*n + indi[j]] = a[i*n + indi[j]] - factor*a[n*k + indi[j]];
                }

                b[i] = b[i] - factor*b[k];
            }
        }

    }
    
    for(int k = 0; k < n; k++) {
        x[indi[k]] = b[k];
    }

    return 0;
}

void make_matrix(double *a, int n, int s) {
    switch (s) {
        case 1:
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    a[n*i + j] = n - max(i + 1, j + 1) + 1;
                }
            }
            break;
        
        case 2:
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    a[n*i + j] = max(i + 1, j + 1);
                }
            }
            break;

        case 3:
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    a[n*i + j] = abs(i - j);
                }
            }
            break;

        case 4:
            for(int i = 0; i < n; i++) {
                for(int j = 0; j < n; j++) {
                    a[n*i + j] = 1/(i + j + 1);
                }
            }
            break;
    }
}

void find_error_rate(double *r, int n, double* x, double *b, int s, double *a) { 
    double tmp1 = 0;
    double sum = 0;
    double tmp2 = 0;
    switch(s) {
        case 1:
            for(int i = 0; i < n; i++) {
                sum = 0;
                for(int j = 0; j < n; j++) {
                    sum += a[i*n + j]*x[j];
                }
                tmp1 += fabs(sum - b[i]);
                tmp2 += fabs(b[i]);
            }
            *r = tmp1/tmp2;
            break;

        case 2:
            for(int i = 0; i < n; i++) {
                sum += fabs(x[i] - ((i + 1)%2));
                tmp1 += abs((i + 1)%2);
            }
            *r = sum/tmp1;
            break;
    }
}
            
            
            

                    

