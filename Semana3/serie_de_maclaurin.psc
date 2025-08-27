Algoritmo serie_de_maclaurin
	Definir contador Como Entero
	contador <- 0
	Definir x Como Real
	Definir errors, errora, eulerx, factorial, contfactorial, eulerx2 Como Real
	Escribir 'Ingrese la variable x para el numero de euler'
	Leer x
	Escribir 'Ingrese el error máximo permitido en %'
	Leer errors
	eulerx <- 0
	eulerx2 <- 0
	Repetir
		factorial <- 1
		Si contador = 0 Entonces
			eulerx <- 1 
			contfactorial <- 1
		SiNo
			Repetir
				factorial <- factorial * contfactorial
				contfactorial <- contfactorial + 1
			Hasta Que contfactorial > contador
		Fin Si
		eulerx <- eulerx + (x ^ contador)/factorial
		errora <- (abs((eulerx - eulerx2)/eulerx))*100
		contador <- contador + 1 
		eulerx2 <- eulerx
		contfactorial <- 1
	Hasta Que errora <= errors
	Escribir 'El resultado para el número de euler de la variable x=' x 'es =' eulerx
FinAlgoritmo
