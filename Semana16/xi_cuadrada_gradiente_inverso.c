#include <stdio.h>
#include <math.h>

#define P 4
#define MAXN 6000

int leer_archivo(const char *ruta, double aw[], double xe[], int *n);
double promedio(const double v[], int n);
double evaluar_peleg(const double t[P], double a);
double evaluar_dlp(const double t[P], double a, int *ok);
int resolver_4x4(double A[P][P], double b[P], double x[P]);

int ajustar_modelo(int modelo, const double aw[], const double xe[], int n,
                   double t[P], int max_iter, double tol,
                   double *chi2, double *rmse, double *r2aj)
{
    double lam = 1e-3;
    double th[P]; for (int i=0;i<P;++i) th[i]=t[i];
    double mejor[P]; for (int i=0;i<P;++i) mejor[i]=th[i];
    double mejor_chi2 = INFINITY;

    for (int it=0; it<max_iter; ++it) {
        double JTJ[P][P], JTr[P];
        for (int i=0;i<P;++i){ JTr[i]=0.0; for (int j=0;j<P;++j) JTJ[i][j]=0.0; }
        double chi2_it = 0.0;
        int usados = 0;

        for (int i=0;i<n;++i) {
            double a = aw[i], x = xe[i];
            double y, r, d0, d1, d2, d3;
            if (modelo==0) {
                double a_b1 = pow(a, th[1]);
                double a_b3 = pow(a, th[3]);
                y = th[0]*a_b1 + th[2]*a_b3;
                r = x - y;
                d0 = a_b1;
                d1 = th[0]*a_b1*log(a);
                d2 = a_b3;
                d3 = th[2]*a_b3*log(a);
                usados++;
            } else {
                int ok = 0;
                y = evaluar_dlp(th, a, &ok);
                if (!ok) continue;
                r = x - y;
                double z = log(-log(a));
                d0 = 1.0; d1 = z; d2 = z*z; d3 = z*z*z;
                usados++;
            }
            double J[P] = {d0,d1,d2,d3};
            for (int u=0;u<P;++u){ JTr[u] += J[u]*r; for (int v=0;v<P;++v) JTJ[u][v] += J[u]*J[v]; }
            chi2_it += r*r;
        }
        if (usados < P) return -1;

        for (int d=0; d<P; ++d) JTJ[d][d] += lam;

        double delta[P];
        if (resolver_4x4(JTJ, JTr, delta) != 0) return -1;

        double th_n[P]; for (int i=0;i<P;++i) th_n[i]=th[i]+delta[i];

        double chi2_n = 0.0;
        int usados_n = 0;
        for (int i=0;i<n;++i) {
            double a = aw[i], x = xe[i], y;
            if (modelo==0) {
                y = th_n[0]*pow(a, th_n[1]) + th_n[2]*pow(a, th_n[3]);
                usados_n++;
            } else {
                int ok=0; y = evaluar_dlp(th_n, a, &ok);
                if (!ok) continue; else usados_n++;
            }
            double r = x - y;
            chi2_n += r*r;
        }
        if (usados_n < P) chi2_n = INFINITY;

        double nd=0.0; for (int i=0;i<P;++i) nd += delta[i]*delta[i];

        if (chi2_n < chi2_it) {
            for (int i=0;i<P;++i) th[i]=th_n[i];
            if (chi2_n < mejor_chi2) { mejor_chi2 = chi2_n; for (int i=0;i<P;++i) mejor[i]=th[i]; }
            lam *= 0.5;
            if (nd < tol) break;
        } else {
            lam *= 10.0;
        }
    }

    for (int i=0;i<P;++i) t[i]=mejor[i];

    double ybar = promedio(xe, n);
    double sst = 0.0; for (int i=0;i<n;++i){ double d=xe[i]-ybar; sst += d*d; }

    double ss = 0.0; int neff=0;
    for (int i=0;i<n;++i) {
        int ok=1; double y;
        if (modelo==0) y = evaluar_peleg(t, aw[i]);
        else           y = evaluar_dlp(t, aw[i], &ok);
        if (!ok) continue;
        double r = xe[i]-y; ss += r*r; neff++;
    }
    if (neff < P) return -1;

    double r2  = (sst>0.0)? 1.0 - ss/sst : 0.0;
    double r2a = 1.0 - ((1.0 - r2) * ((double)(neff-1)/(double)(neff-P)));
    *chi2 = ss;
    *rmse = sqrt(ss/(double)neff);
    *r2aj = r2a;
    return 0;
}

int main(void){
    double aw[MAXN], xe[MAXN]; int n=0;

    leer_archivo("Tareas/RB_25.txt", aw, xe, &n);
    leer_archivo("Tareas/RB_35.txt", aw, xe, &n);
    leer_archivo("Tareas/RB_45.txt", aw, xe, &n);
    printf("Puntos leidos: %d\n", n);

    double t_peleg[P] = {1.0,1.0,1.0,1.0};
    double t_dlp[P]   = {1.0,1.0,1.0,1.0};
    double chi2P, rmseP, r2aP, chi2D, rmseD, r2aD;

    int rcP = ajustar_modelo(0, aw, xe, n, t_peleg, 200, 1e-10, &chi2P, &rmseP, &r2aP);
    int rcD = ajustar_modelo(1, aw, xe, n, t_dlp,   200, 1e-10, &chi2D, &rmseD, &r2aD);

    if (rcP==0){
        printf("\nModelo PELEG\n");
        printf("b0= %.10g  b1= %.10g  b2= %.10g  b3= %.10g\n", t_peleg[0], t_peleg[1], t_peleg[2], t_peleg[3]);
        printf("chi2= %.10g  RMSE= %.10g  R2_aj= %.6f\n", chi2P, rmseP, r2aP);
    } else {
        printf("\n[PELEG] no convergio o datos insuficientes\n");
    }

    if (rcD==0){
        printf("\nModelo DLP\n");
        printf("b0= %.10g  b1= %.10g  b2= %.10g  b3= %.10g\n", t_dlp[0], t_dlp[1], t_dlp[2], t_dlp[3]);
        printf("chi2= %.10g  RMSE= %.10g  R2_aj= %.6f\n", chi2D, rmseD, r2aD);
    } else {
        printf("\n[DLP] no convergio o datos insuficientes\n");
    }

    if (rcP==0 && rcD==0){
        if (chi2P < chi2D) printf("\nMEJOR MODELO: PELEG (menor chi2)\n");
        else               printf("\nMEJOR MODELO: DLP (menor chi2)\n");
    }
    return 0;
}

int leer_archivo(const char *ruta, double aw[], double xe[], int *n){
    FILE *f = fopen(ruta,"r");
    if(!f) return 1;
    int k = *n;
    while (k < MAXN){
        double a,x; int r=fscanf(f,"%lf %lf",&a,&x);
        if (r==2){ aw[k]=a; xe[k]=x; k++; }
        else if (r==EOF) break;
        else { int c; do{ c=fgetc(f);}while(c!='\n'&&c!=EOF); }
    }
    fclose(f);
    *n = k;
    return 0;
}

double promedio(const double v[], int n){ double s=0.0; for(int i=0;i<n;++i) s+=v[i]; return s/(n>0?n:1); }
double evaluar_peleg(const double t[P], double a){ return t[0]*pow(a,t[1]) + t[2]*pow(a,t[3]); }
double evaluar_dlp(const double t[P], double a, int *ok){
    if (a<=0.0 || a>=1.0){ if(ok) *ok=0; return NAN; }
    if (ok) *ok=1;
    double z = log(-log(a));
    return t[0] + t[1]*z + t[2]*z*z + t[3]*z*z*z;
}

int resolver_4x4(double A[P][P], double b[P], double x[P]){
    for (int k=0;k<4;++k){
        int p=k; double m=fabs(A[k][k]);
        for (int i=k+1;i<4;++i){ double v=fabs(A[i][k]); if(v>m){m=v;p=i;} }
        if (m<1e-14) return -1;
        if (p!=k){ for(int j=0;j<4;++j){ double t=A[k][j]; A[k][j]=A[p][j]; A[p][j]=t; } double tb=b[k]; b[k]=b[p]; b[p]=tb; }
        for (int i=k+1;i<4;++i){ double f=A[i][k]/A[k][k]; A[i][k]=0.0; for(int j=k+1;j<4;++j) A[i][j]-=f*A[k][j]; b[i]-=f*b[k]; }
    }
    for (int i=3;i>=0;--i){ double s=b[i]; for (int j=i+1;j<4;++j) s-=A[i][j]*x[j]; x[i]=s/A[i][i]; }
    return 0;
}
//