#include <math.h>
#include <stdio.h>
#define N 3

void imprimir_raices(const double A[N][N+1]);
int eliminacion_adelante(double A[N][N+1]);
int sustitucion(const double A[N][N+1], double x[N]);
void swap_rows(double A[N][N+1], int r1, int r2);
int asegurar_pivote(double A[N][N+1], int k);

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

int sustitucion(const double A[N][N+1], double x[N]) {
    for (int i = N-1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i+1; j < N; ++j) {
            sum += A[i][j] * x[j];
        }
        double denom = A[i][i];
        if (fabs(denom) < 1e-12) return -1;
        x[i] = (A[i][N] - sum) / denom;
    }
    return 0;
}

int eliminacion_adelante(double A[N][N+1]) {
    for (int k = 0; k < N-1; ++k) {
        if (asegurar_pivote(A, k) != 0) return -1;
        double eliminador = A[k][k];
        for (int i = k+1; i < N; ++i) {
            double m = A[i][k] / eliminador;
            A[i][k] = 0.0;
            for (int j = k+1; j < N+1; ++j) {
                A[i][j] -= m * A[k][j];
            }
        }
    }
    if (fabs(A[N-1][N-1]) < 1e-12) return -1;
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
