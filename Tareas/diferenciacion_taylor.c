#include <stdio.h>
#include <math.h>

int main()
{
    float x_1, x, x_11, fx_1, fx, fx_11, h ;
    float dif_adelante, dif_atras, dif_centrada, e_ade, e_atra, e_cent = 0;
    float Valor_verdadero = 0;

    printf("Bienvenido al programa para calcular derivadas usando Taylor \n");

    printf("Para empezar ingresa el valor de x_(i-1):  ");
    scanf("%f", &x_1);
    printf("Ingresa el valor de f(x_(i-1)):  ");
    scanf("%f", &fx_1);

    printf("\nIngresa el valor de x:  ");
    scanf("%f", &x);
    printf("Ingresa el valor de f(x):  ");
    scanf("%f", &fx);

    printf("\nIngresa el valor de x_(i+1):  ");
    scanf("%f", &x_11);
    printf("Ingresa el valor de f(x_(i+1)):  ");
    scanf("%f", &fx_11);

    printf("\nIngresa el valor verdadero:  ");
    scanf("%f", &Valor_verdadero);

    h = x-x_1;

    dif_adelante = (fx_11-fx)/(x_11-x);
    dif_atras = (fx-fx_1)/h;
    dif_centrada = (fx_11-fx_1)/(2*h);

    e_ade = fabsf((Valor_verdadero-dif_adelante)/Valor_verdadero);
    e_atra = fabsf((Valor_verdadero-dif_atras)/Valor_verdadero);
    e_cent = fabsf((Valor_verdadero-dif_centrada)/Valor_verdadero);

    printf("El valor de la diferencial adelante es: %f, con un error de: %f",dif_adelante, e_ade);
    printf("El valor de la diferencial hacia atras es: %f, con un error de: %f",dif_atras, e_atra);
    printf("El valor de la diferencial centrada es: %f, con un error de: %f", dif_centrada, e_cent);


    return 0;
}
