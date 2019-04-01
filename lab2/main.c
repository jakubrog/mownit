#include <stdio.h>
#include <gsl/gsl_blas.h>
#include <sys/times.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>


double time_diff(clock_t start, clock_t end){
    return (double)(end -  start) / sysconf(_SC_CLK_TCK);
}

void print_matirx(gsl_matrix *matrix){
    for(int i = 0 ; i < matrix->size1;i++) {
        for (int k = 0; k < matrix->size2; k++)
            printf("%f  ", gsl_matrix_get(matrix, i, k));
        printf("\n");
    }
}
void print_vector(gsl_vector *vector){
    for(int i = 0; i < vector->size; i++){
        printf("%f  ",gsl_vector_get(vector, i) );
    }
    printf("\n");
}



int main (void)
{
    FILE * fp;
    fp = fopen("result.csv", "w+");
    if(!fp){
        printf("Cannot open a file.");
        return -1;
    }
    fprintf(fp,"\"first_vector_matrix_size\";\"second_vector_size\";\"ddot_time\";\"dgemv_time\"\n");

    clock_t start;

    srand(time(NULL));

    for(int j = 1; j <= 4; j++) {
        size_t size = (size_t)j*1000; /// add rand ()
        gsl_vector *vector1 = gsl_vector_calloc(size);
        gsl_vector *vector2 = gsl_vector_calloc(size);
        gsl_matrix *matrix = gsl_matrix_calloc(size, size); // matrix must be square
        gsl_vector *result_dgemv = gsl_vector_calloc(size);



        double *result_ddot = calloc(size, sizeof(double));


        for(size_t k = 0; k < size;k++) {
            gsl_vector_set(vector1, k, rand());// add rand
            gsl_vector_set(vector2, k, rand());
            gsl_matrix_set(matrix, 0, k , gsl_vector_get(vector1, k) );
        }


        for (int i = 0; i < 10; i++) {


            ///gsl_blas_ddot

            start = clock();

            gsl_blas_ddot(vector1, vector2, result_ddot);


            fprintf(fp,"%ld;%ld;%.5f;",size,size,(clock()-start)/(double)CLOCKS_PER_SEC);

            ////gsl_blas_dgemv

            start = clock();

            gsl_blas_dgemv(CblasNoTrans, 1.0, matrix, vector2 ,0.0, result_dgemv);

            fprintf(fp,"%.5f\n",(clock()-start)/(double)CLOCKS_PER_SEC);

            printf("%d.%d\n", j , i);

            if(*result_ddot != gsl_vector_get(result_dgemv, 0)){ ///looking for error
                printf("Different results\n");
                return 1;
            }
        }
        gsl_vector_free(vector1);
        gsl_vector_free(vector2);
        gsl_vector_free(result_dgemv);
        gsl_matrix_free(matrix);
        free(result_ddot);


    }
    fclose(fp);

    return 0;
}
