#include <math.h>
#include <stdio.h>



int main()
{
    printf("Bienvenido al programa de Optimización empleando el método del gradiente\n");
    printf("La función a optimizar es la siguiente: \n f(x,y) = 2xy + 2x -  x^2 -2y^2");
    printf("\nCon las siguientes condiciones iniciales: x0 = -1, yo = 1");

    int x0 = -1;
    int yo = 1;

  //calculo del hessiano

    float deltax2 = -2;
    float deltay2 = -4;
    float deltaxdeltay = 2;

    double Hessiano [2][2] = {{deltax2, deltaxdeltay}, {deltaxdeltay, deltay2}};

    double determinante = Hessiano[0][0]*Hessiano[1][1] - Hessiano[0][1]*Hessiano[1][0];

    printf("El determinante es %lf", determinante);





    return 0;
}

