#include <stdio.h>
#include <math.h>

double f(double x){ return 2.0*sin(x) - (x*x)/10.0; }

static void ordenar4(double *x0,double *f0,double *x1,double *f1,double *x2,double *f2,double *x3,double *f3){
    if(*x0>*x1){ double tx=*x0;*x0=*x1;*x1=tx; double tf=*f0;*f0=*f1;*f1=tf; }
    if(*x1>*x2){ double tx=*x1;*x1=*x2;*x2=tx; double tf=*f1;*f1=*f2;*f2=tf; }
    if(*x2>*x3){ double tx=*x2;*x2=*x3;*x3=tx; double tf=*f2;*f2=*f3;*f3=tf; }
    if(*x0>*x1){ double tx=*x0;*x0=*x1;*x1=tx; double tf=*f0;*f0=*f1;*f1=tf; }
    if(*x1>*x2){ double tx=*x1;*x1=*x2;*x2=tx; double tf=*f1;*f1=*f2;*f2=tf; }
}

double maximo_interpolacion_cubica(double x0,double x1,double x2,double x3,double tol,int max_iter,int *iters){
    double f0=f(x0), f1=f(x1), f2=f(x2), f3=f(x3);
    ordenar4(&x0,&f0,&x1,&f1,&x2,&f2,&x3,&f3);
    for(int k=0;k<max_iter;++k){
        double d01=(f1-f0)/(x1-x0);
        double d12=(f2-f1)/(x2-x1);
        double d23=(f3-f2)/(x3-x2);
        double d012=(d12-d01)/(x2-x0);
        double d123=(d23-d12)/(x3-x1);
        double d0123=(d123-d012)/(x3-x0);

        double s1=x0+x1+s1, s2=x0*x1 + x0*x2 + x1*x2; /* placeholder to silence warnings */
        (void)s1; (void)s2;

        double a=d0123;
        double b=d012 - (x0+x1+x2)*d0123;
        double c=d01  - (x0+x1)*d012 + (x0*x1 + x0*x2 + x1*x2)*d0123;
        double d=f0   - d01*x0 + d012*(x0*x1) - d0123*(x0*x1*x2);

        double xnew;
        if (fabs(a) < 1e-14){
            if (fabs(b) < 1e-14) xnew = 0.5*(x0+x3);
            else xnew = -c/(2.0*b);
        } else {
            double disc = b*b - 3.0*a*c;
            if (disc < 0.0){
                xnew = -b/(3.0*a);
            } else {
                double r1 = (-b + sqrt(disc))/(3.0*a);
                double r2 = (-b - sqrt(disc))/(3.0*a);
                double y1 = a*r1*r1*r1 + b*r1*r1 + c*r1 + d;
                double y2 = a*r2*r2*r2 + b*r2*r2 + c*r2 + d;
                int ok1 = (r1>x0 && r1<x3);
                int ok2 = (r2>x0 && r2<x3);
                if (ok1 && ok2) xnew = (y1>=y2)? r1 : r2;
                else if (ok1)   xnew = r1;
                else if (ok2)   xnew = r2;
                else            xnew = 0.5*(x0+x3);
            }
        }
        if (!(xnew>x0 && xnew<x3) || isnan(xnew) || isinf(xnew)) xnew = 0.5*(x0+x3);
        double fnew = f(xnew);

        double xx[5]={x0,x1,x2,x3,xnew};
        double ff[5]={f0,f1,f2,f3,fnew};
        int imin=0; for(int i=1;i<5;++i) if(ff[i]<ff[imin]) imin=i;

        double nx[4], nf[4]; int p=0;
        for(int i=0;i<5;++i) if(i!=imin){ nx[p]=xx[i]; nf[p]=ff[i]; ++p; }
        x0=nx[0]; f0=nf[0]; x1=nx[1]; f1=nf[1]; x2=nx[2]; f2=nf[2]; x3=nx[3]; f3=nf[3];
        ordenar4(&x0,&f0,&x1,&f1,&x2,&f2,&x3,&f3);

        double fbest = f1; int ibest=1;
        if (f2>fbest){ fbest=f2; ibest=2; }
        if (f0>fbest){ fbest=f0; ibest=0; }
        if (f3>fbest){ fbest=f3; ibest=3; }
        double xbest = (ibest==0?x0:ibest==1?x1:ibest==2?x2:x3);

        if (fabs(x3-x0) < tol || fabs(xnew - xbest) < tol || fabs(fnew - fbest) < tol){
            if (iters) *iters = k+1;
            return xbest;
        }
    }
    if (iters) *iters = max_iter;
    double fbest = f1; int ibest=1;
    if (f2>fbest){ fbest=f2; ibest=2; }
    if (f0>fbest){ fbest=f0; ibest=0; }
    if (f3>fbest){ fbest=f3; ibest=3; }
    return (ibest==0?x0:ibest==1?x1:ibest==2?x2:x3);
}

int main(void){
    double x0=0.0, x1=0.8, x2=1.6, x3=2.4;
    double tol=1e-10; int max_iter=200, it=0;
    double x = maximo_interpolacion_cubica(x0,x1,x2,x3,tol,max_iter,&it);
    double fx = f(x);
    printf("Maximo aproximado por interpolacion polinomial cubica:\n");
    printf("x* = %.12f\n", x);
    printf("f(x*) = %.12f\n", fx);
    printf("iteraciones = %d\n", it);
    return 0;
}
