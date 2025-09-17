#include <stdio.h>
#include <math.h>

float funcion1(float x) {
    return sinf(10.0f*x) - cosf(3.0f*x);
}

// Este código usa biseccion para encontrar todas las raices en [3,5].

int main() {
    float xmin, xmax, h, x0, x1, fx0, fx1;
    float a, b, a0, b0, k, K_old, err_max, err_ir, Ea_final, Ea_teo;
    float k_last = 1e9f;
    int cont, total = 0;

    xmin = 3.0f;
    xmax = 5.0f;
    h = 0.01f;
    err_max = 0.001f;

    x0 = xmin;
    fx0 = funcion1(x0);

    while (x0 < xmax) {
        x1 = x0 + h;
        if (x1 > xmax) x1 = xmax;
        fx1 = funcion1(x1);

        if (fx0 == 0.0f) {
            printf("Raiz exacta en x = %f\n", x0);
            total++;
        } else if (fx0 * fx1 < 0.0f) {
            a = x0; b = x1;
            a0 = a; b0 = b;
            cont = 0;
            err_ir = 1.0f;
            K_old = 0.0f;

            while (err_ir > err_max && cont <= 200) {
                k = (a + b) / 2.0f;
                if (cont > 0) {
                    err_ir = fabsf((k - K_old) / (k != 0.0f ? k : 1.0f));
                }
                if (funcion1(k) * funcion1(a) < 0.0f) {
                    b = k;
                } else {
                    a = k;
                }
                K_old = k;
                cont++;
            }

            Ea_final = 0.5f * (b - a);
            Ea_teo = (b0 - a0) / powf(2.0f, (float)cont);

            if (fabsf(k - k_last) > 1e-4f) {
                total++;
                printf("Raiz #%d: x = %f, iteraciones = %d, Er = %f, Ea_final = %f, Ea_teo = %f, %s\n",
                       total, k, cont, err_ir, Ea_final, Ea_teo,
                       (fabsf(Ea_final - Ea_teo) <= 1e-6f*(1.0f + fabsf(Ea_teo))) ? "Ea=dx/2^n: SI" : "Ea=dx/2^n: NO");
                k_last = k;
            }
        }

        x0 = x1;
        fx0 = fx1;
    }

    if (total == 0) {
        printf("No se detectaron raices en [3,5].\n");
    } else {
        printf("Total de raices encontradas: %d\n", total);
    }

    return 0;
}
