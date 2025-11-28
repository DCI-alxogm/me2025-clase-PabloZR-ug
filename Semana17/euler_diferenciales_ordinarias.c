#include <stdio.h>
#include <math.h>

#define MAXP 10000

double k = 0.3;

double f(double t, double C){ return -k*C; }
double C_exacta(double t, double t0, double C0){ return C0*exp(-k*(t - t0)); }

int euler(double t0, double C0, double tf, double h, double t[], double C[], int maxp){
    int n = 0;
    t[0] = t0; C[0] = C0;
    while (t[n] < tf && n+1 < maxp){
        double paso = h;
        if (t[n] + paso > tf) paso = tf - t[n];
        double Cn1 = C[n] + paso * f(t[n], C[n]);
        double tn1 = t[n] + paso;
        n++;
        t[n] = tn1; C[n] = Cn1;
        if (paso == 0.0) break;
    }
    return n+1;
}

int main(void){
    double t0 = 0.0, C0 = 1.0, tf = 5.0, h = 0.5;
    printf("EDO: dC/dt = -k C\n");
    printf("Ingresa k, C0, t0, tf, h: ");
    if (scanf("%lf %lf %lf %lf %lf", &k, &C0, &t0, &tf, &h) != 5){
        printf("Entrada invalida. Se usan valores por defecto.\n");
    }
    if (h <= 0.0) h = 0.1;
    if (tf <= t0) tf = t0 + 1.0;
    if (k < 0.0) k = -k;

    double t[MAXP], C[MAXP];
    int m = euler(t0, C0, tf, h, t, C, MAXP);

    printf("\nMetodo de Euler para dC/dt = -k C\n");
    printf("k=%.8f, C0=%.8f, t0=%.8f, tf=%.8f, h=%.8f\n\n", k, C0, t0, tf, h);
    printf("%10s %18s %18s %18s\n", "k", "t_k", "C_k (Euler)", "C_exacta");
    for (int i=0; i<m; ++i){
        double Ce = C_exacta(t[i], t0, C0);
        printf("%10d %18.10f %18.10f %18.10f\n", i, t[i], C[i], Ce);
    }

    double Cfin = C[m-1];
    double Cref = C_exacta(t[m-1], t0, C0);
    double err  = fabs(Cfin - Cref);
    printf("\nAproximacion final: C(tf)=%.12f en t=%.6f\n", Cfin, t[m-1]);
    printf("Referencia exacta: C(tf)=%.12f   Error=%.3e\n", Cref, err);
    return 0;
}
