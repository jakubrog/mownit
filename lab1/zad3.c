#include <stdio.h>
#include <gsl/gsl_ieee_utils.h>

int main(void){
        float f = 1.1;
        while(f > 0){
                printf("f= "); gsl_ieee_printf_float(&f);
                printf ("\n");
                f = f/2;
        }
        return 0;
}


