#include <math.h>
#include <stdio.h>
#define N 3

double L[N][N] = {
    {1,0,0},
    {0,1,0},
    {0,0,1}
};

void imprimir_matriz(const double A[N][N]);
void imprimir_matriz_aumentada(const double A[N][N+1]);
void multiplicar_matrices(const double L[N][N], const double U[N][N], double R[N][N]);
void sustitucion_adelante(const double L[N][N], const double b[N], double y[N]);
void sustitucion_atras(const double U[N][N], const double y[N], double x[N]);
int eliminacion_adelante(double A[N][N+1]);

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de Descomposición LU\n");

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

    printf("\nMatriz aumentada ingresada:\n");
    imprimir_matriz_aumentada(matriz);

    eliminacion_adelante(matriz);

    printf("\nMatriz U (triangular superior):\n");
    double U[N][N];
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            U[i][j] = matriz[i][j];
    imprimir_matriz(U);

    printf("\nMatriz L (triangular inferior):\n");
    imprimir_matriz(L);

    double LU[N][N];
    multiplicar_matrices(L, U, LU);
    printf("\nProducto L*U (debe aproximarse a A original):\n");
    imprimir_matriz(LU);

    double b[N] = {matriz[0][N], matriz[1][N], matriz[2][N]};
    double y[N], x[N];
    sustitucion_adelante(L, b, y);
    sustitucion_atras(U, y, x);

    printf("\nVector Y (solución intermedia de LY=B):\n");
    for (int i = 0; i < N; ++i) printf("y%d = %.6f\n", i+1, y[i]);

    printf("\nVector X (solución final de UX=Y):\n");
    for (int i = 0; i < N; ++i) printf("x%d = %.6f\n", i+1, x[i]);

    return 0;
}

int eliminacion_adelante(double A[N][N+1]) {
    for (int k = 0; k < N-1; ++k) {
        double eliminador = A[k][k];
        for (int i = k+1; i < N; ++i) {
            double m = A[i][k] / eliminador;
            L[i][k] = m;
            printf("Valor m= %f con i = %d y k = %d", m, i, k);
            A[i][k] = 0.0;
            for (int j = k+1; j < N+1; ++j) {
                A[i][j] -= m * A[k][j];
            }
        }
    }
    return 0;
}

void multiplicar_matrices(const double L[N][N], const double U[N][N], double R[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) {
                sum += L[i][k] * U[k][j];
            }
            R[i][j] = sum;
        }
    }
}

void sustitucion_adelante(const double L[N][N], const double b[N], double y[N]) {
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j)
            sum += L[i][j] * y[j];
        y[i] = (b[i] - sum) / L[i][i];
    }
}

void sustitucion_atras(const double U[N][N], const double y[N], double x[N]) {
    for (int i = N-1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i+1; j < N; ++j)
            sum += U[i][j] * x[j];
        x[i] = (y[i] - sum) / U[i][i];
    }
}

void imprimir_matriz(const double A[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j)
            printf("%10.6f ", A[i][j]);
        printf("]\n");
    }
}

void imprimir_matriz_aumentada(const double A[N][N+1]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j)
            printf("%10.6f ", A[i][j]);
        printf("| %10.6f ]\n", A[i][N]);
    }
}
