#include <stdio.h>

int main()
{
    float a = 3 ;
    float b = 4 ;
    float c = 5;
    float d = 7;
    float e;

    e = (a+b)*c/d;
    printf("Operaciones a realizar: e = (a+b)*c/d \n %f", e);
    e = ((a+b)*c)/d;
    printf("\nOperaciones a realizar: e = ((a+b)*c)/d \n %f", e);
    e = (a+b) * c/d;
    printf("\nOperaciones a realizar: e = (a+b) * c/d \n %f", e);
    e = a + (b*c)/d;
    printf("\nOperaciones a realizar: e = a + (b*c)/d \n %f", e);


    return 0;
}