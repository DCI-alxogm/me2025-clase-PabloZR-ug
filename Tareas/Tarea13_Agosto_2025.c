#include <stdio.h>

int main() {
    int num;
    printf("Ingresa un número: ");
    scanf("%d", &num);

    if (num % 2 == 0) {
        printf("El número es par.\n");
    } else {
        printf("El número es impar.\n");
    }

    return 0;
}
