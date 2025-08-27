/*
Programa para cálcular las series de Taylor de 5 funciones diferentes
*/

#include <stdio.h>

int main()
{
    char funciones[5]= ("e^x","cos(x)","sen(x)","ln(x)");
    float maxerror; 
    printf("Bienvenido el programa para encontrar soluciones empleando la serie de Taylor...\n");
    printf("Indique cual es el error máximo permitido: ");
    scanf("%f", &maxerror);
    printf("Escoga una de las 5 funciones disponibles a resolver\n");
    printf("1) %c\t2) %c\t3)%c\t4)%c\t5)%c\n");
    
    

    return 0;
}


