#include <stdio.h>
#include <math.h>

#define MAXP 10000

double k = 0.45;
double Cmax = 1.0;

double f(double t, double C){ (void)t; return k * C * (Cmax - C); }

double C_exacta(double t, double t0, double C0){
    double a = Cmax / C0 - 1.0;
    return Cmax / (1.0 + a * exp(-k * Cmax * (t - t0)));
}

int rk4(double t0, double C0, double tf, double h, double t[], double C[], int maxp){
    int n = 0;
    t[0] = t0; C[0] = C0;
    while (t[n] < tf && n+1 < maxp){
        double paso = h;
        if (t[n] + paso > tf) paso = tf - t[n];

        double k1 = f(t[n],             C[n]);
        double k2 = f(t[n] + 0.5*paso,  C[n] + 0.5*paso*k1);
        double k3 = f(t[n] + 0.5*paso,  C[n] + 0.5*paso*k2);
        double k4 = f(t[n] + paso,      C[n] + paso*k3);

        double Cn1 = C[n] + (paso/6.0)*(k1 + 2.0*k2 + 2.0*k3 + k4);
        double tn1 = t[n] + paso;

        n++;
        t[n] = tn1; C[n] = Cn1;
        if (paso == 0.0) break;
    }
    return n+1;
}

int rk2(double t0, double C0, double tf, double h, double t[], double C[], int maxp){
    int n = 0;
    t[0] = t0; C[0] = C0;
    while (t[n] < tf && n+1 < maxp){
        double paso = h;
        if (t[n] + paso > tf) paso = tf - t[n];
        double k1 = f(t[n], C[n]);
        double k2 = f(t[n] + paso, C[n] + paso*k1);
        double Cn1 = C[n] + 0.5*paso*(k1 + k2);
        double tn1 = t[n] + paso;
        n++;
        t[n] = tn1; C[n] = Cn1;
        if (paso == 0.0) break;
    }
    return n+1;
}

int main(void){
    double t0 = 0.0, C0 = 0.02, tf = 25.0, h = 0.1;

    printf("Modelo: dC/dt = k C (Cmax - C)\n");
    printf("Ingresa k, Cmax, C0, t0, tf, h: ");
    if (scanf("%lf %lf %lf %lf %lf %lf", &k, &Cmax, &C0, &t0, &tf, &h) != 6){
        printf("Entrada invalida. Se usan valores por defecto.\n");
        k = 0.45; Cmax = 1.0; C0 = 0.02; t0 = 0.0; tf = 25.0; h = 0.1;
    }
    if (h <= 0.0) h = 0.1;
    if (tf <= t0) tf = t0 + 1.0;
    if (k < 0.0) k = -k;
    if (Cmax <= 0.0) Cmax = 1.0;

    double t4[MAXP], C4[MAXP];
    double t2[MAXP], C2[MAXP];

    int m4 = rk4(t0, C0, tf, h, t4, C4, MAXP);
    int m2 = rk2(t0, C0, tf, h, t2, C2, MAXP);

    printf("\nParametros: k=%.6f, Cmax=%.6f, C0=%.6f, t0=%.2f, tf=%.2f, h=%.3f\n", k, Cmax, C0, t0, tf, h);
    printf("%6s %12s %16s %16s %16s\n", "k", "t", "C_RK4", "C_RK2", "C_exacta");
    int m = (m4 < m2) ? m4 : m2;
    for (int i=0; i<m; ++i){
        double Ce = C_exacta(t4[i], t0, C0);
        printf("%6d %12.3f %16.8f %16.8f %16.8f\n", i, t4[i], C4[i], C2[i], Ce);
    }

    double Cfin4 = C4[m4-1];
    double Cfin2 = C2[m2-1];
    double Cref  = C_exacta(t4[m4-1], t0, C0);
    double err4  = fabs(Cfin4 - Cref);
    double err2  = fabs(Cfin2 - Cref);

    printf("\nFinal RK4: C(tf)=%.10f  Error=%.3e\n", Cfin4, err4);
    printf("Final RK2: C(tf)=%.10f  Error=%.3e\n", Cfin2, err2);
    return 0;
}
