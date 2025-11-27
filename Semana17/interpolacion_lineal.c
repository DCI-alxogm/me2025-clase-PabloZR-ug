#include <stdio.h>
#include <math.h>

double f(double x){ return 2.0*sin(x) - (x*x)/10.0; }
double df(double x){ return 2.0*cos(x) - x/5.0; }

double maximo_interpolacion_lineal(double a,double b,double tol,int max_iter,int *iters){
    double fa = df(a), fb = df(b);
    if (fa*fb > 0.0) return NAN;
    for (int k=0;k<max_iter;++k){
        double denom = fb - fa;
        double x = (fabs(denom) < 1e-14)? 0.5*(a+b) : b - fb*(b-a)/denom;
        double fxp = df(x);
        if (fabs(fxp) < tol || fabs(b-a) < tol){ if(iters) *iters=k+1; return x; }
        if (fa*fxp < 0.0){ b = x; fb = fxp; }
        else             { a = x; fa = fxp; }
    }
    if (iters) *iters = max_iter;
    return 0.5*(a+b);
}

int main(void){
    double a = 0.0, b = 2.0;
    double tol = 1e-12;
    int max_iter = 200, it = 0;

    double x = maximo_interpolacion_lineal(a,b,tol,max_iter,&it);
    double fx = f(x);
    double fpp = -2.0*sin(x) - 0.2;

    printf("Maximo aproximado por interpolacion lineal:\n");
    printf("x* = %.12f\n", x);
    printf("f(x*) = %.12f\n", fx);
    printf("iteraciones = %d\n", it);
    printf("f''(x*) = %.12f\n", fpp);
    return 0;
}
