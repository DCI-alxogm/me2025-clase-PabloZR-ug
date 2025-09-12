
#include <stdio.h>
#include <math.h>

float funcion1(float x) {
    return (9.81*68.1)/x*(1-exp(-(x/68.1)*10)-40);
}

// Este código compara el método de la falsa posición con el de bisección




int main()
{
    float a, b, k, err_max, err_ir, K_old, e_puro, k_falso, k_falso_old;
    float err_ir_falso, e_puro_falso;
    int cont = 1;
    printf("Ingresa el valor de A: ");
    scanf("%f", &a);
    printf("\nIngresa el valor de B: ");
    scanf("%f", &b);
    err_max = 0.05;
    e_puro = 0.05;

    while (((err_ir < err_max) && (e_puro < err_max)) || (cont > 200)) {
        if (cont > 1) {
            k = K_old;
        }
        k= (a+b)/2;
        if (funcion1(k)*funcion1(a)<0) {
            b = k;
        } else {
            a = k;
        }
        if (cont > 0) {
            err_ir = abs((k-K_old)/k);

        }
        e_puro = (k-K_old)/(2^cont);
        cont++;
    }



    return 0;
}