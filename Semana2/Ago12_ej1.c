#include <stdio.h>
#include <math.h>

int main() {
  int numeros[5] = {1,2,3,4,5};
  double resultados[5] = {};
  double pi = 3.1415926534;
  printf("Pi large = %f\n", pi+pi);
  for(int index = 0; index <= 5; index++) {
    double n = numeros[index];
    int par = n;
    if(par % 2 == 0) {
      resultados[index] = log10(n);
    }
    else{
      resultados[index] = exp(n)+cos(n);
      printf("x = %d \n exp(x)+cos(x)=%f\n", par, resultados[index]);
    }
    printf("x\t x^2 \t log(x+1) \t exp(x)+cos(x)");
    printf("\n%f %f %f %f\n", n, n*n, log10(n+1),exp(n)+cos(n));
  }


}