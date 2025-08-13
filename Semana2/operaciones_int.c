#include <stdio.h>

int main()
{
    int a = 3 ;
    int b = 4 ;
    int c = 5;
    int d = 7;
    int e;

    e = (a+b)*c/d;
    printf("Operaciones a realizar: e = (a+b)*c/d \n %d", e);
    e = ((a+b)*c)/d;
    printf("\nOperaciones a realizar: e = ((a+b)*c)/d \n %d", e);
    e = (a+b) * c/d;
    printf("\nOperaciones a realizar: e = (a+b) * c/d \n %d", e);
    e = a + (b*c)/d;
    printf("\nOperaciones a realizar: e = a + (b*c)/d \n %d", e);


    return 0;
}