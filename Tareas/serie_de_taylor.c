#include <stdio.h>
#include <math.h>

int main(){
    int opcion, nmax, k, done = 0;
    double maxerror, x, x0, h, aprox = 0.0, residuo = 0.0;

    printf("Bienvenido al programa de series de Taylor\n");
    printf("Error maximo permitido: ");
    if (scanf("%lf", &maxerror) != 1) return 0;
    printf("Numero maximo de terminos: ");
    if (scanf("%d", &nmax) != 1) return 0;
    printf("Funciones:\n");
    printf("1) e^x\n");
    printf("2) cos(x)\n");
    printf("3) sen(x)\n");
    printf("4) ln(x)\n");
    printf("5) sqrt(x)\n");
    printf("Opcion: ");
    if (scanf("%d", &opcion) != 1) return 0;
    printf("x: ");
    if (scanf("%lf", &x) != 1) return 0;
    printf("x0 (centro): ");
    if (scanf("%lf", &x0) != 1) return 0;

    if ((opcion == 4 || opcion == 5) && (x <= 0.0 || x0 <= 0.0)) { printf("Dominio invalido\n"); return 0; }

    h = x - x0;

    if (opcion == 1){
        double base = exp(x0), sum = 1.0, term = 1.0, next;
        done = 0;
        for (k = 1; k <= nmax; ++k){
            term *= h / k;
            sum += term;
            if (fabs(term) < maxerror){
                next = term * (h / (k + 1));
                aprox = base * sum;
                residuo = fabs(base * next);
                done = 1;
                break;
            }
        }
        if (!done){
            double next = term * (h / (nmax + 1));
            aprox = base * sum;
            residuo = fabs(base * next);
        }
    } else if (opcion == 2){
        double s0 = sin(x0), c0 = cos(x0);
        double sum = 0.0, mon = 1.0, fact = 1.0, term, deriv, next_deriv, next;
        done = 0;
        for (k = 0; k <= nmax; ++k){
            int r = k % 4;
            if (r == 0) deriv = c0;
            else if (r == 1) deriv = -s0;
            else if (r == 2) deriv = -c0;
            else deriv = s0;
            term = deriv * mon / fact;
            sum += term;
            if (k > 0 && fabs(term) < maxerror){
                int r2 = (k + 1) % 4;
                if (r2 == 0) next_deriv = c0;
                else if (r2 == 1) next_deriv = -s0;
                else if (r2 == 2) next_deriv = -c0;
                else next_deriv = s0;
                next = next_deriv * (mon * h) / (fact * (k + 1));
                aprox = sum;
                residuo = fabs(next);
                done = 1;
                break;
            }
            mon *= h;
            fact *= (k + 1);
        }
        if (!done){
            int r2 = (nmax + 1) % 4;
            if (r2 == 0) next_deriv = c0;
            else if (r2 == 1) next_deriv = -s0;
            else if (r2 == 2) next_deriv = -c0;
            else next_deriv = s0;
            double next = next_deriv * (mon * h) / (fact * (nmax + 1));
            aprox = sum;
            residuo = fabs(next);
        }
    } else if (opcion == 3){
        double s0 = sin(x0), c0 = cos(x0);
        double sum = 0.0, mon = 1.0, fact = 1.0, term, deriv, next_deriv, next;
        done = 0;
        for (k = 0; k <= nmax; ++k){
            int r = k % 4;
            if (r == 0) deriv = s0;
            else if (r == 1) deriv = c0;
            else if (r == 2) deriv = -s0;
            else deriv = -c0;
            term = deriv * mon / fact;
            sum += term;
            if (k > 0 && fabs(term) < maxerror){
                int r2 = (k + 1) % 4;
                if (r2 == 0) next_deriv = s0;
                else if (r2 == 1) next_deriv = c0;
                else if (r2 == 2) next_deriv = -s0;
                else next_deriv = -c0;
                next = next_deriv * (mon * h) / (fact * (k + 1));
                aprox = sum;
                residuo = fabs(next);
                done = 1;
                break;
            }
            mon *= h;
            fact *= (k + 1);
        }
        if (!done){
            int r2 = (nmax + 1) % 4;
            if (r2 == 0) next_deriv = s0;
            else if (r2 == 1) next_deriv = c0;
            else if (r2 == 2) next_deriv = -s0;
            else next_deriv = -c0;
            double next = next_deriv * (mon * h) / (fact * (nmax + 1));
            aprox = sum;
            residuo = fabs(next);
        }
    } else if (opcion == 4){
        double y = h / x0, sum = log(x0), term = y, add, next;
        done = 0;
        for (k = 1; k <= nmax; ++k){
            if (k % 2 == 1) add = term / k; else add = -term / k;
            sum += add;
            if (fabs(add) < maxerror){
                term *= y;
                if ((k + 1) % 2 == 1) next = term / (k + 1); else next = -term / (k + 1);
                aprox = sum;
                residuo = fabs(next);
                done = 1;
                break;
            }
            term *= y;
        }
        if (!done){
            term *= y;
            if ((nmax + 1) % 2 == 1) next = term / (nmax + 1); else next = -term / (nmax + 1);
            aprox = sum;
            residuo = fabs(next);
        }
    } else if (opcion == 5){
        double y = h / x0, c = 1.0, mon = 1.0, sum = 1.0, term, c_next, mon_next, next;
        done = 0;
        for (k = 0; k < nmax; ++k){
            c = c * (0.5 - k) / (k + 1.0);
            mon *= y;
            term = c * mon;
            sum += term;
            if (fabs(term) < maxerror){
                c_next = c * (0.5 - (k + 1)) / (k + 2.0);
                mon_next = mon * y;
                next = c_next * mon_next;
                aprox = sqrt(x0) * sum;
                residuo = fabs(sqrt(x0) * next);
                done = 1;
                break;
            }
        }
        if (!done){
            c_next = c * (0.5 - nmax) / (nmax + 1.0);
            mon_next = mon * y;
            next = c_next * mon_next;
            aprox = sqrt(x0) * sum;
            residuo = fabs(sqrt(x0) * next);
        }
    } else {
        printf("Opcion invalida\n");
        return 0;
    }

    printf("Aproximacion: %.15f\n", aprox);
    printf("Residuo estimado: %.15f\n", residuo);
    return 0;
}
