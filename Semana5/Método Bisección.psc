Algoritmo método_bisección
	Definir a, b, k Como Real
	Definir err_max, err_ir, K_old Como Real
	Definir cont Como Entero
	i:= 0
	Escribir 'Ingresa el valor de a'
	Leer a
	Escribir 'Ingresa el valor de b'
	Leer b

	err_max := 0.05
	Mientras err_ir < err_max Hacer
		Si i > 0 Entonces
			k := K_old
		FinSi
		k = (a+b)/2
		Si func(k)*func(a) < 0 Entonces
			b = k
		SiNo
			a = k
		FinSi
		Si i > 0 Entonces
			err_ir = abs((K-K_old)/k)
		FinSi
		
	FinMientras
	
FinAlgoritmo

Funcion f <- func(value)
	Definir f Como Real
	f:= (9.81*68.1)/value*(1-exp(-(value/68.1)*10))-40
FinFuncion