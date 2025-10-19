#include <math.h>
#include <stdio.h>
#define N 3

void imprimir_raices(const double A[N][N+1]);
int eliminacion_adelante(double A[N][N+1]);
int sustitucion(const double A[N][N+1], double x[N]);

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de "
           "gauss simple\n");
    double matriz[3][4] = {0};
    printf("Ingresa la matriz aumentada 3x4.\n");
    printf("Escribe cada fila en una sola línea, separando columnas con espacios (a11 a12 a13 b1).\n");
    for (int i = 0; i < 3; i++) {
        printf("Fila %d: ", i+1);
        for (int j = 0; j < 4; j++) {
            if (scanf("%lf", &matriz[i][j]) != 1) {
                printf("Entrada inválida.\n");
            }
        }
    }
    printf("Matriz aumentada ingresada \n");
    imprimir_raices(matriz);
    eliminacion_adelante(matriz);

    printf("Matriz triangular tras eliminación \n");
    imprimir_raices(matriz);

    double x[N] = {0};
    sustitucion(matriz, x);
    printf("\nSolucion:\n");
    for (int i = 0; i < N; ++i) {
        printf("x%d = %.10g\n", i+1, x[i]);
    }




    return 0;
}

int sustitucion(const double A[N][N+1], double x[N]) {
    for (int i = N-1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i+1; j < N; ++j) {
            sum += A[i][j] * x[j];
        }
        double denom = A[i][i];
        if (fabs(denom) < 1e-12) return -1; // singular
        x[i] = (A[i][N] - sum) / denom;
    }
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
void imprimir_raices(const double A[N][N+1]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j) {
            printf("%10.6f ", A[i][j]);
        }
        printf("| %10.6f ]\n", A[i][N]);
    }
}