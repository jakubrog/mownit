#include <iostream>
#include <iomanip>



// Przykładem algorytmu niestabilnego może być algorytm wyliczania n'tego wyrazu równania rekurencyjnego
// np. x_n = 16/5 * x_n-1 - 3/5*x_n-2 gdzie xo = 1 i x1 = 1/5. Jak  widać do 15 wyrazu ciągu błąd nie jest bardzo duży natomiast po 15 zaczyna

// lub przykład z wykładu z e podnoszonym do ujemnej potegi

using namespace std;

double e_power_x(int power);
double upgraded_e_pow_x(int pow);


int main() {
   double x_n2 = 1;
   double x_n1 = 1.0/5;
   double x_n = 0;

   double better_xn = 1.0/5;
    printf("Wyliczanie wyrażeń ciągu rekurencyjnego:  \n");
   for(int i = 2; i < 100; i++){
       x_n = x_n1*(16.0/5) - (3.0/5)*x_n2;
       better_xn *= 1.0/5;
       printf("%d. Wartość z ciągu rekurencyjnego: %.15f  Wartość z równania charakterystycznego: %.15f \n", i, x_n, better_xn);
       x_n2 = x_n1;
       x_n1 = x_n;
   }

    printf("\n\nWyliczanie kolejnych potęg liczby eulera:  \n");
    for(int i = 3; i>= -7; i--){
        printf("Potega : %d . Szereg Tylora: %0.4f    Poprawiony szereg: %0.4f \n", i , e_power_x(i), upgraded_e_pow_x(i));
    }
    return 0;
}

double e_power_x(int power){
    double e = 1;
    int pow_cpy = power;
    double frac = 1;
    for(int i = 2; i < 10; i++){
        e += power/frac;
        power *= pow_cpy;
        frac *= i;
    }
    return e;
}

double upgraded_e_pow_x(int pow){
    return pow < 0 ? 1/e_power_x((-1)*pow) : e_power_x(pow);
}