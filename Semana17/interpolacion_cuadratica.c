#include <stdio.h>
#include <math.h>

double f(double x){ return 2.0*sin(x) - (x*x)/10.0; }

static void ordenar_por_x(double *x0,double *f0,double *x1,double *f1,double *x2,double *f2){
    if(*x0>*x1){ double tx=*x0;*x0=*x1;*x1=tx; double tf=*f0;*f0=*f1;*f1=tf; }
    if(*x1>*x2){ double tx=*x1;*x1=*x2;*x2=tx; double tf=*f1;*f1=*f2;*f2=tf; }
    if(*x0>*x1){ double tx=*x0;*x0=*x1;*x1=tx; double tf=*f0;*f0=*f1;*f1=tf; }
}

double maximo_interpolacion_cuadratica(double x0,double x1,double x2,double tol,int max_iter,int *iters){
    double f0=f(x0), f1=f(x1), f2=f(x2);
    ordenar_por_x(&x0,&f0,&x1,&f1,&x2,&f2);
    for(int k=0;k<max_iter;++k){
        double A = (x1-x0), B = (x1-x2);
        double N = (A*A)*(f1-f2) - (B*B)*(f1-f0);
        double D = A*(f1-f2)     -  B*(f1-f0);
        double x3;
        if (fabs(D) < 1e-14) x3 = 0.5*(x0+x2);
        else x3 = x1 - 0.5*(N/D);
        if (x3 <= x0 || x3 >= x2 || isnan(x3) || isinf(x3)) x3 = 0.5*(x0+x2);
        double f3 = f(x3);

        double xx[4]={x0,x1,x2,x3};
        double ff[4]={f0,f1,f2,f3};
        int idx_min=0;
        for(int i=1;i<4;++i) if(ff[i]<ff[idx_min]) idx_min=i;

        int p=0;
        double nx[3], nf[3];
        for(int i=0;i<4;++i) if(i!=idx_min){ nx[p]=xx[i]; nf[p]=ff[i]; ++p; }
        x0=nx[0]; f0=nf[0]; x1=nx[1]; f1=nf[1]; x2=nx[2]; f2=nf[2];
        ordenar_por_x(&x0,&f0,&x1,&f1,&x2,&f2);

        if (fabs(x2-x0) < tol || fabs(x3-x1) < tol || fabs(f3-f1) < tol){ if(iters) *iters=k+1; return x1; }
    }
    if(iters) *iters=max_iter;
    return x1;
}

int main(void){
    double x0=0.0, x1=1.0, x2=2.0;
    double tol = 1e-10;
    int max_iter = 200, it=0;

    double xmax = maximo_interpolacion_cuadratica(x0,x1,x2,tol,max_iter,&it);
    double fmax = f(xmax);

    printf("Maximo aproximado:\n");
    printf("x* = %.12f\n", xmax);
    printf("f(x*) = %.12f\n", fmax);
    printf("iteraciones = %d\n", it);
    return 0;
}
