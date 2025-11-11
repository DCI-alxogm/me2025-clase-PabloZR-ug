#include <math.h>
#include <stdio.h>
/*Este programa optimizará una función con el metodo del gradiente
 *y realizará las derivadas con el metodo de diferencias finitas.
*/


int main()
{
    printf("Bienvenido al programa de Optimización empleando el método del gradiente\n");
    printf("La función a optimizar es la siguiente: \n f(x,y) = 2xy + 2x -  x^2 -2y^2");
    printf("\nCon las siguientes condiciones iniciales: x0 = -1, yo = 1");

    int x0 = -1;
    int yo = 1;

    float deltax2 = -2;
    float deltay2 = -4;
    float deltaxdeltay = 2;

    double Hessiano [2][2] = {{deltax2, deltaxdeltay}, {deltaxdeltay, deltay2}};

    double determinante = Hessiano[0][0]*Hessiano[1][1] - Hessiano[0][1]*Hessiano[1][0];

    printf("El determinante es %lf", determinante);

    double gx = 2.0*yo + 2.0 - 2.0*x0;
    double gy = 2.0*x0 - 4.0*yo;
    printf("\nDireccion pk = grad f(xk, yk) en (x0, yo): [%.6f, %.6f]\n", gx, gy);

    double x = (double)x0;
    double y = (double)yo;
    double tol = 1e-10;
    int max_iter = 1000;
    int iter = 0;
    double alpha = 0.0;

    while (iter < max_iter) {
        double fx = 2.0*x*y + 2.0*x - x*x - 2.0*y*y;

        gx = 2.0*y + 2.0 - 2.0*x;
        gy = 2.0*x - 4.0*y;

        double Hg_x = Hessiano[0][0]*gx + Hessiano[0][1]*gy;
        double Hg_y = Hessiano[1][0]*gx + Hessiano[1][1]*gy;
        double gTg  = gx*gx + gy*gy;
        double gTHg = gx*Hg_x + gy*Hg_y;
        if (gTg < tol) break;
        alpha = - gTg / gTHg;

        double x_new = x + alpha*gx;
        double y_new = y + alpha*gy;

        double gx_new = 2.0*y_new + 2.0 - 2.0*x_new;
        double gy_new = 2.0*x_new - 4.0*y_new;
        double g_inf = fabs(gx_new) > fabs(gy_new) ? fabs(gx_new) : fabs(gy_new);

        double step_dx = fabs(x_new - x);
        double step_dy = fabs(y_new - y);
        double step_inf = step_dx > step_dy ? step_dx : step_dy;

        double f_new = 2.0*x_new*y_new + 2.0*x_new - x_new*x_new - 2.0*y_new*y_new;
        double df = fabs(f_new - fx);

        x = x_new;
        y = y_new;

        if (g_inf < tol || step_inf < tol || df < tol) break;

        iter++;
    }

    printf("alpha* = %.10f\n", alpha);
    printf("x* = %.10f, y* = %.10f\n", x, y);
    double fstar = 2.0*x*y + 2.0*x - x*x - 2.0*y*y;
    printf("f(x*,y*) = %.10f\n", fstar);

    return 0;
}
