
#include <stdio.h>
#include <math.h>


float funcion1(float x) {
    return powf(x,10) - 1;
}

// Este código compara el metodo de la falsa posicion con el metodo de biseccion.




int main()
{
    float a, b, k, err_max, err_ir, K_old, e_puro, k_falso, k_falso_old;
    float err_ir_falso, e_puro_falso;
    int cont = 1;
    printf("Ingresa el valor de A: ");
    scanf(" %f", &a);
    printf("Ingresa el valor de B: ");
    scanf(" %f", &b);
    err_max = 0.05;
    e_puro = 0.99;
    err_ir = 0.99;





    while (((err_ir > err_max) && (e_puro > err_max)) || (cont < 200)) {

        k_falso = ((funcion1(b)*a)-(funcion1(a)*b))/(funcion1(b)-funcion1(a));
        k= (a+b)/2;
        if (funcion1(k)*funcion1(a)<0) {
            b = k;
        } else {
            a = k;
        }
        if (cont > 1) {
            err_ir = fabsf((k-K_old)/k);
            err_ir_falso = fabsf((k_falso-k_falso_old)/k_falso);
        }
        e_puro = (k-K_old)/pow(2,cont);


        k_falso_old = k_falso;
        K_old = k;
        cont++;
    }
    printf("El contador llegó a: %d", cont);
    printf("El valor obtenido para la raiz usando el metodo de biseccion es el siguiente: %f, con un error de "
           "%f", k,err_ir);
    printf("\n El valor obtenido para la raiz usando el metodo de falsa posicion el siguiente: %f, con un error de"
           " %f", k_falso, err_ir_falso);


    return 0;
}