#include <stdio.h>
#include <math.h>

static inline double relerr(double x1, double x0){
    double den = fmax(1.0, fabs(x1));
    return fabs(x1 - x0)/den;
}
static void header(const char* t){
    printf("%s\n", t);
    printf("%-5s %-18s %-18s %-10s\n","Iter","x(i+1)","f(x(i+1))","Error %");
}

/* ===================== Caso 1: f1(x)=exp(-x)-x ===================== */
static double f1(double x){ return exp(-x) - x; }
static double f1p(double x){ return -exp(-x) - 1.0; }
static double f1pp(double x){ return exp(-x); }
static double g1(double x){ return exp(-x); } /* punto fijo */

void fijo_f1(double x0, double tol, int itmax){
    header("Método del punto fijo (f1):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double x1 = g1(x);
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f1(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void newton_f1(double x0, double tol, int itmax){
    header("Método de Newton-Raphson (f1):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f1(x), fpx=f1p(x);
        if(fabs(fpx)<1e-16){ puts("Derivada ~0. Aborto."); return; }
        double x1 = x - fx/fpx;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f1(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void secante_f1(double x0, double x1, double tol, int itmax){
    header("Método de la Secante (f1):");
    double a=x0,b=x1, fa=f1(a), fb=f1(b);
    for(int k=0;k<itmax;k++){
        double den = fb-fa;
        if(fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x2 = b - fb*(b-a)/den;
        double e = relerr(x2,b);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x2,f1(x2),100.0*e);
        if(e<tol) return;
        a=b; b=x2; fa=fb; fb=f1(b);
    }
}
void halley_f1(double x0, double tol, int itmax){
    header("Método de Newton mod. (Halley) (f1):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f1(x), fpx=f1p(x), fppx=f1pp(x);
        double den = 2.0*fpx*fpx - fx*fppx;
        if(fabs(fpx)<1e-16 || fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x1 = x - (2.0*fx*fpx)/den;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f1(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}

/* ===================== Caso 2: f2(x)=x^10-1 ===================== */
static double f2(double x){ return pow(x,10.0) - 1.0; }
static double f2p(double x){ return 10.0*pow(x,9.0); }
static double f2pp(double x){ return 90.0*pow(x,8.0); }
static double g2(double x){ return x - 0.1*(pow(x,10.0) - 1.0); } /* contracción */

void fijo_f2(double x0, double tol, int itmax){
    header("Método del punto fijo (f2):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double x1 = g2(x);
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f2(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void newton_f2(double x0, double tol, int itmax){
    header("Método de Newton-Raphson (f2):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f2(x), fpx=f2p(x);
        if(fabs(fpx)<1e-16){ puts("Derivada ~0. Aborto."); return; }
        double x1 = x - fx/fpx;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f2(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void secante_f2(double x0, double x1, double tol, int itmax){
    header("Método de la Secante (f2):");
    double a=x0,b=x1, fa=f2(a), fb=f2(b);
    for(int k=0;k<itmax;k++){
        double den = fb-fa;
        if(fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x2 = b - fb*(b-a)/den;
        double e = relerr(x2,b);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x2,f2(x2),100.0*e);
        if(e<tol) return;
        a=b; b=x2; fa=fb; fb=f2(b);
    }
}
void halley_f2(double x0, double tol, int itmax){
    header("Método de Newton mod. (Halley) (f2):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f2(x), fpx=f2p(x), fppx=f2pp(x);
        double den = 2.0*fpx*fpx - fx*fppx;
        if(fabs(fpx)<1e-16 || fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x1 = x - (2.0*fx*fpx)/den;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f2(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}

/* ========== Caso 3: f3(x)=x^3-5x^2-7x-3 (dos semillas: 0 y 4) ========== */
static double f3(double x){ return x*x*x - 5.0*x*x - 7.0*x - 3.0; }
static double f3p(double x){ return 3.0*x*x - 10.0*x - 7.0; }
static double f3pp(double x){ return 6.0*x - 10.0; }
static double g3(double x){ return cbrt(5.0*x*x + 7.0*x + 3.0); } /* estable */

void fijo_f3(double x0, double tol, int itmax){
    header("Método del punto fijo (f3):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double x1 = g3(x);
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f3(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void newton_f3(double x0, double tol, int itmax){
    header("Método de Newton-Raphson (f3):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f3(x), fpx=f3p(x);
        if(fabs(fpx)<1e-16){ puts("Derivada ~0. Aborto."); return; }
        double x1 = x - fx/fpx;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f3(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}
void secante_f3(double x0, double x1, double tol, int itmax){
    header("Método de la Secante (f3):");
    double a=x0,b=x1, fa=f3(a), fb=f3(b);
    for(int k=0;k<itmax;k++){
        double den = fb-fa;
        if(fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x2 = b - fb*(b-a)/den;
        double e = relerr(x2,b);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x2,f3(x2),100.0*e);
        if(e<tol) return;
        a=b; b=x2; fa=fb; fb=f3(b);
    }
}
void halley_f3(double x0, double tol, int itmax){
    header("Método de Newton mod. (Halley) (f3):");
    double x=x0;
    for(int k=0;k<itmax;k++){
        double fx=f3(x), fpx=f3p(x), fppx=f3pp(x);
        double den = 2.0*fpx*fpx - fx*fppx;
        if(fabs(fpx)<1e-16 || fabs(den)<1e-16){ puts("Denominador ~0. Aborto."); return; }
        double x1 = x - (2.0*fx*fpx)/den;
        double e = relerr(x1,x);
        printf("%-5d %-18.12f %-18.12e %-10.6f\n",k,x1,f3(x1),100.0*e);
        if(e<tol) return;
        x=x1;
    }
}

int main(void){
    const double tol = 1e-8;  /* fracción */
    const int itmax = 50;
    const double h = 0.1;

    puts("\n================================================================");
    puts("f(x) = exp(-x) - x,  x0 = 0,  h = 0.1\n");
    fijo_f1(0.0, tol, itmax); puts("");
    newton_f1(0.0, tol, itmax); puts("");
    secante_f1(0.0, 0.0+h, tol, itmax); puts("");
    halley_f1(0.0, tol, itmax);

    puts("\n================================================================");
    puts("f(x) = x^10 - 1,  x0 = 0.5,  h = 0.1\n");
    fijo_f2(0.5, tol, itmax); puts("");
    newton_f2(0.5, tol, itmax); puts("");
    secante_f2(0.5, 0.5+h, tol, itmax); puts("");
    halley_f2(0.5, tol, itmax);

    puts("\n================================================================");
    puts("f(x) = x^3 - 5x^2 - 7x - 3,  x0 = 0,  h = 0.1\n");
    fijo_f3(0.0, tol, itmax); puts("");
    newton_f3(0.0, tol, itmax); puts("");
    secante_f3(0.0, 0.0+h, tol, itmax); puts("");
    halley_f3(0.0, tol, itmax);

    puts("\n================================================================");
    puts("f(x) = x^3 - 5x^2 - 7x - 3,  x0 = 4,  h = 0.1\n");
    fijo_f3(4.0, tol, itmax); puts("");
    newton_f3(4.0, tol, itmax); puts("");
    secante_f3(4.0, 4.0+h, tol, itmax); puts("");
    halley_f3(4.0, tol, itmax);

    return 0;
}
