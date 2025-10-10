#include <math.h>
#include <stdio.h>
#define N 3

void imprimir_raices(const double A[N][N+1]);
int eliminacion_adelante(double A[N][N+1]);

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de "
           "gauss simple\n");
    double matriz[3][4] = {0};
    for (int i = 0; i < 3; i++) {
        printf("Ingresa los elementos de la primera fila separador por espacios:\n"
          "Fila %d (a%d1 a%d2 a%d3 b%d): ", i+1, i+1, i+1, i+1, i+1);
        for (int j = 0; j < 4; j++) {
            scanf("%lf", &matriz[i][j]);
        }
    }

#hola



    return 0;
}

int eliminacion_adelante(double A[N][N+1]) {
    for (int k = 0; k < N-1; ++k) {
        double eliminador = A[k][k];
        if (fabs(eliminador) < 1e-12) {
            // pivote cero (o numericamente muy pequeño) -> no podemos continuar sin pivoteo
            return -1;
        }

        for (int i = k+1; i < N; ++i) {
            double m = A[i][k] / eliminador;  // multiplicador
            A[i][k] = 0.0;               // explicitamente 0 la columna
            for (int j = k+1; j < N+1; ++j) {
                A[i][j] -= m * A[k][j];
            }
        }
    }
}
void imprimir_raices(const double A[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j) {
            printf("%10.6f ", A[i][j]);
        }
        printf("| %10.6f ]\n", A[i][N]);
    }
}