/*
 *Factorización LU mejorada para el proyecto de métodos numéricos
 *Hecho por: Pablo Ignacio Zorrilla Romo
*/
#include <math.h>
#include <stdio.h>
#define N 9 //Aquí defin´i el tamaño de la matriz. Se modific´o con respecto al original

double L[N][N] = {0};

void imprimir_matriz(const double A[N][N]); //Funciones para imprimir matrices
void imprimir_matriz_aumentada(const double A[N][N+1]); //Funciones para imprimir matrices
void multiplicar_matrices(const double L[N][N], const double U[N][N], double R[N][N]); // Verifica la descomposición (LxU)
void sustitucion_adelante(const double L[N][N], const double b[N], double y[N]); //Resuelve el triangulito de matrices
void sustitucion_atras(const double U[N][N], const double y[N], double x[N]); //Resuelve un triangulito de matrices inverso
int eliminacion_adelante(double A[N][N+1]); // Realiza la descomposición A=LU y resuelve Ly=b

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de Descomposición LU\n");
    for (int i = 0; i < N; ++i) L[i][i] = 1.0;

    double matriz[N][N+1] = {
        { 4, -1,  0, -1,  0,  0,  0,  0,  0, 150},
        {-1,  4, -1,  0, -1,  0,  0,  0,  0, 100},
        { 0, -1,  4,  0,  0, -1,  0,  0,  0, 150},
        {-1,  0,  0,  4, -1,  0, -1,  0,  0,  50},
        { 0, -1,  0, -1,  4, -1,  0, -1,  0,   0},
        { 0,  0, -1,  0, -1,  4,  0,  0, -1,  50},
        { 0,  0,  0, -1,  0,  0,  4, -1,  0,  70},
        { 0,  0,  0,  0, -1,  0, -1,  4, -1,  20},
        { 0,  0,  0,  0,  0, -1,  0, -1,  4,  70}
    };// Matriz obtenida en el PDF

    printf("\nMatriz aumentada:\n");
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
    printf("\nProducto L*U (aprox A):\n");
    imprimir_matriz(LU);
//Explicación de la metodologia en cada una de las funciones
    double y[N], x[N];
    for (int i = 0; i < N; ++i) y[i] = matriz[i][N];   // ya es y = L^{-1} b
    printf("\nVector Y (LY=B):\n");
    for (int i = 0; i < N; ++i) printf("y%d = %.6f\n", i+1, y[i]);

    sustitucion_atras(U, y, x);                       // x = U^{-1} y

    printf("\nVector X (UX=Y):\n");
    for (int i = 0; i < N; ++i) printf("x%d = %.6f\n", i+1, x[i]);

    return 0;
}
/*
 *Itera sobre cada columna pivote
 * Realiza un procedimiento similar a gauss jordan calculando el multiplicador y eliminando elementos
 * Estos elementos son sustituidos con 0
 * Esta funcion esta explicada con más detalle en el metodo gauss jordan
 * Pero en este caso la operación se realizaa toda la fila incluidad la columna del vector b
 * Por lo tanto on solo se transforma a en u si no que también se transforma b en y.
*/
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
//Función sencilla de multiplicación de matrices
void multiplicar_matrices(const double Lm[N][N], const double Um[N][N], double R[N][N]) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            double sum = 0.0;
            for (int k = 0; k < N; ++k) sum += Lm[i][k] * Um[k][j];
            R[i][j] = sum;
        }
    }
}
//Realiza la sustitución hacía adelante iterando de arriba hacia abajo i=0 a N-1
void sustitucion_adelante(const double Lm[N][N], const double b[N], double y[N]) {
    for (int i = 0; i < N; ++i) {
        double sum = 0.0;
        for (int j = 0; j < i; ++j) sum += Lm[i][j] * y[j];
        y[i] = (b[i] - sum) / Lm[i][i];
    }
}
//Itera de abajo hacia arriba de i = N-1 a 0
void sustitucion_atras(const double Um[N][N], const double y[N], double x[N]) {
    for (int i = N-1; i >= 0; --i) {
        double sum = 0.0;
        for (int j = i+1; j < N; ++j) sum += Um[i][j] * x[j];
        x[i] = (y[i] - sum) / Um[i][i];
    }
}
//Loops de impresión de matrices
void imprimir_matriz(const double A[N][N]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j) printf("%10.6f ", A[i][j]);
        printf("]\n");
    }
}
//Loops de impresión de matrices
void imprimir_matriz_aumentada(const double A[N][N+1]) {
    for (int i = 0; i < N; ++i) {
        printf("[ ");
        for (int j = 0; j < N; ++j) printf("%10.6f ", A[i][j]);
        printf("| %10.6f ]\n", A[i][N]);
    }
}
