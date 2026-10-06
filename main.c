#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "header.h"

int main(int argc, char* argv[]) {
    const int task = 16;
    int i = 0, j = 0; //индексы
    int n = 0, s = 0; //разряд матрицы и способ заполнения
    int r = 0; //размер матрицы для вывода
    double r1 = 0, r2 = 0; //неувязка
    double t1 = 0, t2 = 0; //время работы алгоритма решения СЛУ и алгоритма вычисления r1, r2
    double* a = NULL; //матрица
    double* b = NULL; //правая часть
    double* x = NULL; //столбец неизвестных
    FILE* filename = NULL;
    char* endptr = NULL;
    time_t start_time, end_time;

    if(argc < 4) {
        printf("Необходимо ввести все аргументы!\n");
        return -1;
    }

    n = strtol(argv[1], &endptr, 10);
    if (((*endptr != '\0') && (*endptr != '\n')) || n <= 0)
	{
		printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
	}
    endptr = NULL;

    r = strtol(argv[2], &endptr, 10);
    if (((*endptr != '\0') && (*endptr != '\n')) || r <= 0)
	{
		printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
	}
    endptr = NULL;

    s = strtol(argv[3], &endptr, 10);
    if ((*endptr != '\0') && (*endptr != '\n'))
	{
		printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
	}
    endptr = NULL;

    if(s == 0) {
        if(argc < 5) { printf("Необходимо ввести название файла\n"); return -1;}
        filename = fopen(argv[4], "r");
        if(filename == NULL) {
            printf("Не удалось открыть файл\n");
            fclose(filename);
            return -1;
        }
    }

    a = (double*)malloc(n * n * sizeof(double));
    if(a == NULL) {
        free(a);
        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
    }

    x = (double*)malloc(n * sizeof(double));

    int* indi = (int*)malloc(n * sizeof(int)); //массив номеров строк
    if(indi == NULL) {
        free(indi);
        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
    }


    if(s == 0) {
        for(i = 0; i < n; i++) {
            for(j = 0; j < n; j++) {
                if(fscanf(filename, "%lf", &a[i*n + j]) != 1) {
                    printf("Не удалось считать данные из файла %d %d \n", i, j);
                    fclose(filename);
                    free(a);
                    return -1;

                }
            }
        }  
    }
    else { make_matrix(a, n, s);} 

    b = (double*)malloc(n * sizeof(double));
    if(b == NULL) {
        free(b);
        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
		return -1;
    }
    
    for(int i = 0; i < n; i++) {
        for(int k = 0; k < (n - 2)/2; k++) {
            b[i] += a[n*i + 2*k + 1];
        }
        b[i] += a[n*i + n - 1];
    }

   /**for(int i = 0; i < r; i++) {
        for(int j = 0; j < r; j++) {
            printf("%10.3lf ", a[i*n + j]);
        }
        printf("\n");
    }**/

    start_time = time(NULL);
    if(jordan_algorithm(a, indi, b, &x, n, 0.00001) == 0) {
        end_time = time(NULL);
        t1 = (double)end_time - (double)start_time;
    
        start_time = time(NULL);
        find_error_rate(&r1, n, x, b, 1, a);
        find_error_rate(&r2, n, x, b, 2, a);
        end_time = time(NULL);
        t2  = (double)end_time - (double)start_time;

        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
        for(int i = 0; i < r; i++) {
            printf("%10.3lf", x[i]);
            printf("\n");
        }

        for(int i = 0; i < r; i++) {
            for(int j = 0; j < r; j++) {
                printf("%10.3lf ", a[i*n + j]);
            }
            printf("\n");
        }
    }
    else {
        end_time = time(NULL);
        t1 = start_time - end_time;
        r1 = -1;
        r2 = -1;
        t2 = 0;
        printf("%s : Task = %d Res1 = %e Res2 = %e T1 = %.2f T2 = %.2f S = %d N = %d\n",argv[0], task, r1, r2, t1, t2, s, n);
    }
    return 0;
}
