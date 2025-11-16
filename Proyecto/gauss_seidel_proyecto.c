/*
*metodo gauss-seide mejorado para el proyecto de métodos numéricos
 *Hecho por: Pablo Ignacio Zorrilla Romo
*/
#include <math.h>
#include <stdio.h>
#define N 9 //Cambio de dimensión con respecto al programa original

void imprimir_raices(const double A[N][N+1]); //Funci´n impresión matrices como en otros códigs
int gauss_seidel(const double A[N][N], const double b[N], double x[N], double tol, int max_iter, double w);
//Función del metodo iterativo con una tolerancia dada "función encontrada parcialmente en internet"
void matvec(const double A[N][N], const double x[N], double y[N]); //Multiplicación de matriz-vector
double norm_inf_vec(const double v[N]);
//Calcula la norma del vector

int main()
{
    printf("Bienvenido al programa de resolución de matrices por el método de gauss-seidel\n");
    printf("Se resolverá la matriz 9x9 \n");

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
    };
//Matriz obtenida en el documento PDF

    printf("Matriz aumentada ingresada \n");
    imprimir_raices(matriz);

    double A[N][N], b[N], x[N] = {0};
    for (int i = 0; i < N; ++i) {
        b[i] = matriz[i][N];
        for (int j = 0; j < N; ++j) A[i][j] = matriz[i][j];
    }
//Aqui se dividio la matriz ingresada en sus dos compnentes el A y el b para
    //Tener una forma de Ax=b


//Llamada al solver dandole la tolerancia maxima permitida.
    int rc = gauss_seidel(A, b, x, 1e-10, 10000, 1.0);
    if (rc != 0) {
        printf("[ERROR] Gauss-Seidel no convergio\n");
        return 1;
    }

    printf("\nSolucion:\n");
    for (int i = 0; i < N; ++i) {
        printf("x%d = %.10g\n", i+1, x[i]);
    }
    return 0;
}

int gauss_seidel(const double A[N][N], const double b[N], double x[N], double tol, int max_iter, double w) {
    double x_old[N];
    for (int iter = 0; iter < max_iter; ++iter) {
        //Se establece un criterio para detener si se llega a un maximo de iteracion
        for (int i = 0; i < N; ++i) x_old[i] = x[i];
        //Al inicio de cada iteracion se copiara la solució´n actual
        for (int i = 0; i < N; ++i) {
            //Ciclo para iterarar sobre cada fila para calcular el xi nuevo
            double s1 = 0.0, s2 = 0.0;
            for (int j = 0; j < i; ++j) s1 += A[i][j] * x[j];
            for (int j = i+1; j < N; ++j) s2 += A[i][j] * x_old[j];
            if (fabs(A[i][i]) < 1e-14) return -1;
            double x_new = (b[i] - s1 - s2) / A[i][i];
            x[i] = (1.0 - w) * x[i] + w * x_new;
        }
        double diff[N];
        for (int i = 0; i < N; ++i) diff[i] = x[i] - x_old[i];
        if (norm_inf_vec(diff) < tol) return 0;
    }
    return -2;
}



void matvec(const double A[N][N], const double x[N], double y[N]) {
    for (int i = 0; i < N; ++i) {
        double s = 0.0;
        for (int j = 0; j < N; ++j) s += A[i][j] * x[j];
        y[i] = s;
    }
}

double norm_inf_vec(const double v[N]) {
    double m = 0.0;
    for (int i = 0; i < N; ++i) {
        double a = fabs(v[i]);
        if (a > m) m = a;
    }
    return m;
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
