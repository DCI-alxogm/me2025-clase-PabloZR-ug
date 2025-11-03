#include <math.h>
#include <stdio.h>

void imprimir_matriz_nn(int n, const double A[n][n]);
void imprimir_matriz_nm(int n, int m, const double B[n][m]);
void multiplicar_matrices_nn(int n, const double L[n][n], const double U[n][n], double R[n][n]);
void sustitucion_adelante_nm(int n, int m, const double L[n][n], const double B[n][m], double Y[n][m]);
void sustitucion_atras_nm(int n, int m, const double U[n][n], const double Y[n][m], double D[n][m]);
int eliminacion_adelante_n(int n, double U[n][n], double L[n][n]);

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de Descomposición LU\n");

    int n;
    printf("Ingresa la dimensión de la matriz A (n x n): ");
    if (scanf("%d", &n) != 1 || n <= 0) return 1;

    double A0[n][n];
    printf("Ingresa la matriz A de %d x %d.\n", n, n);
    for (int i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for (int j = 0; j < n; j++) {
            if (scanf("%lf", &A0[i][j]) != 1) return 1;
        }
    }

    int m;
    printf("Ingresa el número de columnas de B (n x m): ");
    if (scanf("%d", &m) != 1 || m <= 0) return 1;

    double B[n][m];
    printf("Ingresa la matriz B de %d x %d.\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("Fila %d: ", i+1);
        for (int j = 0; j < m; j++) {
            if (scanf("%lf", &B[i][j]) != 1) return 1;
        }
    }

    printf("\nMatriz A ingresada:\n");
    imprimir_matriz_nn(n, A0);
    printf("\nMatriz B ingresada:\n");
    imprimir_matriz_nm(n, m, B);

    double L[n][n], U[n][n];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            L[i][j] = (i == j) ? 1.0 : 0.0;
            U[i][j] = A0[i][j];
        }
    }

    eliminacion_adelante_n(n, U, L);

    printf("\nMatriz U (triangular superior):\n");
    imprimir_matriz_nn(n, U);

    printf("\nMatriz L (triangular inferior):\n");
    imprimir_matriz_nn(n, L);

    double LU[n][n];
    multiplicar_matrices_nn(n, L, U, LU);
    printf("\nProducto L*U (debe aproximarse a A original):\n");
    imprimir_matriz_nn(n, LU);

    double Y[n][m], D[n][m];
    sustitucion_adelante_nm(n, m, L, B, Y);
    sustitucion_atras_nm(n, m, U, Y, D);

    printf("\nMatriz Y (solución intermedia de LY=B):\n");
    imprimir_matriz_nm(n, m, Y);

    printf("\nMatriz D (solución final de UX=Y):\n");
    imprimir_matriz_nm(n, m, D);

    return 0;
}

int eliminacion_adelante_n(int n, double U[n][n], double L[n][n]) {
    for (int k = 0; k < n-1; ++k) {
        double piv = U[k][k];
        for (int i = k+1; i < n; ++i) {
            double m = U[i][k] / piv;
            L[i][k] = m;
            printf("Valor m= %f con i = %d y k = %d", m, i, k);
            U[i][k] = 0.0;
            for (int j = k+1; j < n; ++j) {
                U[i][j] -= m * U[k][j];
            }
        }
    }
    return 0;
}

void multiplicar_matrices_nn(int n, const double L[n][n], const double U[n][n], double R[n][n]) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            double s = 0.0;
            for (int k = 0; k < n; ++k) s += L[i][k] * U[k][j];
            R[i][j] = s;
        }
    }
}

void sustitucion_adelante_nm(int n, int m, const double L[n][n], const double B[n][m], double Y[n][m]) {
    for (int r = 0; r < m; ++r) {
        for (int i = 0; i < n; ++i) {
            double s = 0.0;
            for (int j = 0; j < i; ++j) s += L[i][j] * Y[j][r];
            Y[i][r] = (B[i][r] - s) / L[i][i];
        }
    }
}

void sustitucion_atras_nm(int n, int m, const double U[n][n], const double Y[n][m], double D[n][m]) {
    for (int r = 0; r < m; ++r) {
        for (int i = n-1; i >= 0; --i) {
            double s = 0.0;
            for (int j = i+1; j < n; ++j) s += U[i][j] * D[j][r];
            D[i][r] = (Y[i][r] - s) / U[i][i];
        }
    }
}

void imprimir_matriz_nn(int n, const double A[n][n]) {
    for (int i = 0; i < n; ++i) {
        printf("[ ");
        for (int j = 0; j < n; ++j) printf("%10.6f ", A[i][j]);
        printf("]\n");
    }
}

void imprimir_matriz_nm(int n, int m, const double B[n][m]) {
    for (int i = 0; i < n; ++i) {
        printf("[ ");
        for (int j = 0; j < m; ++j) printf("%10.6f ", B[i][j]);
        printf("]\n");
    }
}
