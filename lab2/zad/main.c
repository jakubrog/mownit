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
    fprintf(fp,"\"matrix\";\"first vector(matrix) size\";\"second matrix size\";\"time\"\n");

    clock_t r_time[3] = {0, 0, 0};
    struct tms* tms_time[3];

    for (int i = 0; i < 3; i++) {
        tms_time[i] = malloc(sizeof(struct tms*));
    }

    int current_time = 0;

    for(int j = 0; j < 150; j++) {
        size_t size = 14; /// add rand ()
        gsl_vector *vector1 = gsl_vector_calloc(size);
        gsl_vector *vector2 = gsl_vector_calloc(size);
        gsl_matrix *matrix = gsl_matrix_calloc(size, size); // matrix must be square
        gsl_vector *result_dgemv = gsl_vector_calloc(size);



        double *result_ddot = calloc(size, sizeof(double));


        for(size_t k = 0; k < size;k++) {
            gsl_vector_set(vector1, k, k*k+1);// add rand
            gsl_vector_set(vector2, k, k/2+2);
            gsl_matrix_set(matrix, 0, k , gsl_vector_get(vector1, k) );
        }


        for (int i = 0; i < 10; i++) {
            ///gsl_blas_ddot
            current_time = 0 ;

            r_time[current_time] = times(tms_time[current_time]);
            current_time++;

            gsl_blas_ddot(vector1, vector2, result_ddot);

            r_time[current_time] = times(tms_time[current_time]);
            current_time++;


            fprintf(fp,"false;%ld;%ld;%f\n",size,size,time_diff(r_time[current_time-2], r_time[current_time-1]));

            ////gsl_blas_dgemv
            current_time = 0;
            r_time[current_time] = times(tms_time[current_time]);
            current_time++;


            gsl_blas_dgemv(CblasNoTrans, 1.0, matrix, vector2 ,0.0, result_dgemv);


            r_time[current_time] = times(tms_time[current_time]);
            current_time++;

            fprintf(fp,"true;%ld;%ld;%f\n",size,size,time_diff(r_time[current_time-2], r_time[current_time-1]));

            if(*result_ddot != gsl_vector_get(result_dgemv, 0)){ /// temporary looking for error
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

