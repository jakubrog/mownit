#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


void naive_multiplication(double **A, double **B, double **C, int A_rows, int A_columns, int B_columns, int B_rows) {
    int i, j, k;

    for (i = 0; i < B_columns; i++) {
        for (j = 0; j < A_columns; j++) {
            for (k = 0; k < A_rows; k++){
                C[i][j] += A[i][k] * B[k][j];
              }
        }
    }
}

void better_multiplication(double **A, double **B, double **C, int A_rows, int A_columns, int B_columns, int B_rows) {
    int i, j, k;

    for (k = 0; k < A_rows; k++) {
        C[k] = (double *) malloc(B_columns * sizeof(double));
        for (j = 0; j < A_columns; j++) {
            for (i = 0; i < B_columns; i++)
                C[k][i] += A[k][j] * B[j][i];
        }
    }
}

void print_matrix(double **A, const int A_rows, const int A_columns) {
    for (int i = 0; i < A_rows; i++) {
        printf("\n");
        for (int j = 0; j < A_columns; j++)
            printf("%f\t", A[i][j]);
    }
    printf("\n\n");
}

void print_gsl_matrix(gsl_matrix *matrix, const int A_rows, const int A_columns) {
    for (int i = 0; i < A_rows; i++) {
        printf("\n");
        for (int j = 0; j < A_columns; j++)
            printf("%f\t", gsl_matrix_get(matrix, i, j));
    }
    printf("\n\n");
}

double **create_matrix(int rows, int columns) {
    double **A = (double **) malloc(rows * sizeof(double *));

    for (int i = 0; i < rows; i++)
        A[i] = (double *) malloc(columns * sizeof(double));

    return A;
}

void random_fill(double **A, int A_rows, int A_columns) {
    srand(time(NULL));
    for (int i = 0; i < A_rows; i++)
        for (int j = 0; j < A_columns; j++)
            A[i][j] = rand();
}

void set_matrix(gsl_matrix *matrix, double **A, int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            gsl_matrix_set(matrix, i, j, A[i][j]);
}

void set_to_zero(double **A, int r, int c) {
    for (int i = 0; i < r; i++)
        for (int j = 0; j < c; j++)
            A[i][j] = 0;
}


int main(int argc, char **argv) {

    FILE *fp;
    fp = fopen(argv[1], "w+");
    if (!fp) {
        printf("Cannot open a file.");
        return -1;
    }
    fprintf(fp, "columns_and_rows;naive_multiplication_time;better_multiplication_time;blas_time\n");


    for (int i = 50; i <= 1000; i += 50) {
        for (int j = 0; j < 10; j++) {
            fprintf(fp, "%d;", i);

            double **A = create_matrix(i, i);

            double **B = create_matrix(i, i);

            double **C = create_matrix(i, i);
            set_to_zero(C, i, i);


            gsl_matrix *matrix_A = gsl_matrix_calloc((size_t) i, (size_t) i);
            gsl_matrix *matrix_B = gsl_matrix_calloc((size_t) i, (size_t) i);
            gsl_matrix *matrix_result = gsl_matrix_calloc((size_t) i, (size_t) i);

            random_fill(A, i, i);
            random_fill(B, i, i);

            set_matrix(matrix_A, A, i, i);
            set_matrix(matrix_B, B, i, i);

            clock_t start, end;



            /// NAIVE MULTIPLICATION TIME MEASUREMENT

            start = clock();

            naive_multiplication(A, B, C, i, i, i, i);

            end = clock();

            fprintf(fp, "%lf;", (end - start) / (double) CLOCKS_PER_SEC);

            /// BETTER MULTIPLICATION TIME MEASUREMENT
            set_to_zero(C, i, i);
            start = clock();

            better_multiplication(A, B, C, i, i, i, i);

            end = clock();

            fprintf(fp, "%lf;", (end - start) / (double) CLOCKS_PER_SEC);

            /// BLAS MULTIPLICATION TIME MEASUREMENT

            start = clock();

            gsl_blas_dgemm(CblasNoTrans, CblasNoTrans, 1.0, matrix_B, matrix_A, 0.0, matrix_result);

            end = clock();

            fprintf(fp, "%lf\n", (end - start) / (double) CLOCKS_PER_SEC);

            gsl_matrix_free(matrix_A);
            gsl_matrix_free(matrix_B);
            gsl_matrix_free(matrix_result);
            free(A);
            free(B);
            free(C);
        }
    }

    fclose(fp);

    return 0;
}
