#include <stdio.h>
#include <math.h>

int main() {
    int contador = 0, contfactorial;
    double x, errors, errora, eulerx, factorial, eulerx2;
    printf("Ingrese la variable x para el numero de euler\n");
    scanf("%lf", &x);
    printf("Ingrese el error maximo permitido en %%\n");
    scanf("%lf", &errors);
    eulerx = 0;
    eulerx2 = 0;
    do {
        factorial = 1;
        if (contador == 0) {
            eulerx = 1;
            contfactorial = 1;
        } else {
            contfactorial = 1;
            do {
                factorial = factorial * contfactorial;
                contfactorial = contfactorial + 1;
            } while (contfactorial <= contador);
        }
        eulerx = eulerx + pow(x, contador) / factorial;
        errora = fabs((eulerx - eulerx2) / eulerx) * 100.0;
        contador = contador + 1;
        eulerx2 = eulerx;
        contfactorial = 1;
    } while (errora > errors);
    printf("El resultado para el numero de euler de la variable x= %g es = %g\n", x, eulerx);
    return 0;
}
