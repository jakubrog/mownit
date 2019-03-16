#include <stdio.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_linalg.h>

/* Dimension of Matrix and Vectors */
#define DIM 5

int main(void)
{
    int i, j, lotkin_signum, frank_signum;
    gsl_matrix *lotkin_a, *frank_a;
    gsl_vector *x, *lotkin_b, *frank_b, *lotkin_x, *frank_x;
    gsl_permutation *lotkin_perm, *frank_perm;

    /* allocate a, x, b */
    lotkin_a = gsl_matrix_calloc(DIM, DIM);
    frank_a = gsl_matrix_calloc(DIM, DIM);
    x = gsl_vector_calloc(DIM);
    lotkin_b = gsl_vector_calloc(DIM);
    frank_b = gsl_vector_calloc(DIM);
    lotkin_x = gsl_vector_calloc(DIM);
    frank_x = gsl_vector_calloc(DIM);

    printf("%d", gsl_blas_dgemv(CblasNoTrans, 1.0, lotkin_a, x, 0.0, lotkin_b));

    for(i = 0; i < DIM; i++)
        gsl_vector_set(x, i, (double)i);


    for(i = 0; i < DIM; i++)
        gsl_matrix_set(lotkin_a, 0, i, 1.0);
    for(i = 1; i < DIM; i++)
        for(j = 0; j < DIM; j++)
            gsl_matrix_set(lotkin_a, i, j, 1.0 / (double)(i + j + 1));

    /* set Frank matrix       */
    /* a_ij = DIM - min(i,j) + 1 */
    for(i = 0; i < DIM; i++)
        for(j = 0; j < DIM; j++)
            gsl_matrix_set(frank_a, i, j, (double)DIM - (double)GSL_MAX(i, j) );

    /* Print matrix */
    printf("Lotkin Matrix(DIM = %d)\n", DIM);
    for(i = 0; i < DIM; i++)
    {
        printf("%3d: ", i);
        for(j = 0; j < DIM; j++)
            printf("%g ", gsl_matrix_get(lotkin_a, i, j));
        printf("\n");
    }
    printf("\n");
    printf("Frank Matrix(DIM = %d)\n", DIM);
    for(i = 0; i < DIM; i++)
    {
        printf("%3d: ", i);
        for(j = 0; j < DIM; j++)
            printf("%g ", gsl_matrix_get(frank_a, i, j));
        printf("\n");
    }
    printf("\n");

    /* b = A * x */
    gsl_blas_dgemv(CblasNoTrans, 1.0, lotkin_a, x, 0.0, lotkin_b);
    gsl_blas_dgemv(CblasNoTrans, 1.0, frank_a, x, 0.0, frank_b);

    /* LU decomposition and forward&backward substition */
    lotkin_perm = gsl_permutation_alloc(DIM);
    gsl_linalg_LU_decomp(lotkin_a, lotkin_perm, &lotkin_signum);
    gsl_linalg_LU_solve(lotkin_a, lotkin_perm, lotkin_b, lotkin_x);
    gsl_permutation_free(lotkin_perm);

    frank_perm = gsl_permutation_alloc(DIM);
    gsl_linalg_LU_decomp(frank_a, frank_perm, &frank_signum);
    gsl_linalg_LU_solve(frank_a, frank_perm, frank_b, frank_x);
    gsl_permutation_free(frank_perm);

    /* print */
    printf("index     Lotkin          Frank          True\n");
    for(i = 0; i < DIM; i++)
        printf("%3d %25.17e %25.17e %25.17e\n", i, gsl_vector_get(lotkin_x, i), gsl_vector_get(frank_x, i), gsl_vector_get(x, i));

    /* free a, x, b */
    gsl_matrix_free(lotkin_a);
    gsl_matrix_free(frank_a);
    gsl_vector_free(x);
    gsl_vector_free(lotkin_b);
    gsl_vector_free(frank_b);
    gsl_vector_free(lotkin_x);
    gsl_vector_free(frank_x);

    return 0;
}