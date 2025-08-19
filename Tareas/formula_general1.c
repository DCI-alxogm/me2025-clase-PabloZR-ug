#include <stdio.h>
#include <math.h>

int main() {
    int repetir = 1;
    while (repetir == 1) {
        double a, b, c;
        double discriminante, x1, x2, real, imag;
        int opcion;

        printf("Resolver ax^2 + bx + c = 0\n");
        printf("Ingresa a, b y c separados por espacio: ");
        if (scanf("%lf %lf %lf", &a, &b, &c) != 3) {
            printf("Entrada invalida.\n");
        } else {
            if (a == 0 && b == 0 && c == 0) {
                printf("Identidad 0=0: infinitas soluciones.\n");
            } else if (a == 0 && b == 0) {
                printf("Contradiccion: sin solucion.\n");
            } else if (a == 0) {
                x1 = -c / b;
                printf("Ecuacion lineal. Solucion unica real: x = %.5f\n", x1);
            } else {
                discriminante = b*b - 4*a*c;
                if (discriminante > 0) {
                    x1 = (-b + sqrt(discriminante)) / (2*a);
                    x2 = (-b - sqrt(discriminante)) / (2*a);
                    printf("Dos raices reales distintas:\n");
                    printf("x1 = %.5f\n", x1);
                    printf("x2 = %.5f\n", x2);
                } else if (discriminante == 0) {
                    x1 = -b / (2*a);
                    printf("Raiz doble real: x = %.5f\n", x1);
                } else {
                    real = -b / (2*a);
                    imag = sqrt(-discriminante) / (2*a);
                    printf("Dos raices complejas conjugadas:\n");
                    printf("x1 = %.5f + %.5fi\n", real, imag);
                    printf("x2 = %.5f - %.5fi\n", real, imag);
                }
            }
        }

        printf("¿Deseas resolver otra vez? (1 = Si, 0 = No): ");
        scanf("%d", &opcion);
        if (opcion == 1) {
            repetir = 1;
        } else {
            repetir = 0;
        }
    }
    return 0;
}
