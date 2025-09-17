
#include <stdio.h>
#include <math.h>


float funcion1(float x) {
    return powf(x,10) - 1;
}

// Este código compara el metodo de la falsa posicion con el metodo de biseccion.




int main() {
    float a, b, k, err_max, err_ir, K_old, e_puro, k_falso, k_falso_old;
    float err_ir_falso, e_puro_falso, a_f, b_f;
    int cont = 1;
    printf("Ingresa el valor de A: ");
    scanf(" %f", &a);
    printf("Ingresa el valor de B: ");
    scanf(" %f", &b);
    err_max = 0.0005;
    e_puro = 0.99;
    err_ir = 0.99;
    a_f = a;
    b_f = b;

    if (funcion1(a) * funcion1(b) <= 0.0f) {
        while ((err_ir > err_max || err_ir_falso > err_max) && cont <= 200) {
            k_falso = ((funcion1(b_f) * a_f) - (funcion1(a_f) * b_f)) / (funcion1(b_f) - funcion1(a_f));
            k = (a + b) / 2;
            if (funcion1(k) * funcion1(a) < 0) {
                b = k;
            } else {
                a = k;
            }
            if ((funcion1(a_f) * funcion1(k_falso)) < 0) {
                b_f = k_falso;
            } else {
                a_f = k_falso;
            }
            if (cont > 1) {
                err_ir = fabsf((k - K_old) / k);
                err_ir_falso = fabsf((k_falso - k_falso_old) / k_falso);
                e_puro = (k - K_old) / powf(2, cont);
            }



            k_falso_old = k_falso;
            K_old = k;
            cont++;
        }
    }
    printf("El contador llegó a: %d", cont);
    printf("El valor obtenido para la raiz usando el metodo de biseccion es el siguiente: %f, con un error de "
           "%f", k,err_ir);
    printf("\n El valor obtenido para la raiz usando el metodo de falsa posicion el siguiente: %f, con un error de"
           " %f", k_falso, err_ir_falso);


    return 0;
}