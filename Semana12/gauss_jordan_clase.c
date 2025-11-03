#include <math.h>
#include <stdio.h>
#define N 3

void imprimir_raices(const double A[N][N+1]);
int gauss_jordan(double A[N][N+1]);
void swap_rows(double A[N][N+1], int r1, int r2);
int asegurar_pivote(double A[N][N+1], int k);

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de "
           "gauss-jordan\n");
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
    gauss_jordan(matriz);

    printf("Matriz reducida (Gauss-Jordan) \n");
    imprimir_raices(matriz);

    printf("\nSolucion:\n");
    for (int i = 0; i < N; ++i) {
        printf("x%d = %.10g\n", i+1, matriz[i][N]);
    }

    return 0;
}

void swap_rows(double A[N][N+1], int r1, int r2) {
    if (r1 == r2) return;
    for (int j = 0; j < N+1; ++j) {
        double temp = A[r1][j];
        A[r1][j] = A[r2][j];
        A[r2][j] = temp;
    }
}

int asegurar_pivote(double A[N][N+1], int k) {
    int r = k;
    double best = fabs(A[k][k]);
    for (int i = k+1; i < N; ++i) {
        double v = fabs(A[i][k]);
        if (v > best) {
            best = v;
            r = i;
        }
    }
    if (best < 1e-12) return -1;
    swap_rows(A, k, r);
    return 0;
}

int gauss_jordan(double A[N][N+1]) {
    for (int k = 0; k < N; ++k) {
        if (asegurar_pivote(A, k) != 0) return -1;
        double pivote = A[k][k];
        for (int j = 0; j < N+1; ++j) {
            A[k][j] /= pivote;
        }
        for (int i = 0; i < N; ++i) {
            if (i == k) continue;
            double m = A[i][k];
            for (int j = 0; j < N+1; ++j) {
                A[i][j] -= m * A[k][j];
            }
        }
    }
    return 0;
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
