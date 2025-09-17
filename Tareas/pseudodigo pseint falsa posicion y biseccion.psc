Algoritmo METODO_BISECCION
	Definir a, b, k Como Real
	Definir err_max, err_ir, K_old Como Real
	Definir k_falso, k_falso_old, err_ir_falso, a_f, b_f Como Real
	Definir cont Como Entero
	cont <- 1
	Escribir 'Ingresa el valor de a'
	Leer a
	Escribir 'Ingresa el valor de b'
	Leer b
	err_max <- 0.0005
	err_ir <- 0.99
	err_ir_falso <- 0.99
	a_f <- a
	b_f <- b
	Si func(a)*func(b)<=0 Entonces
		Mientras ((err_ir>err_max O err_ir_falso>err_max) Y cont<=200) Hacer
			k_falso <- ((func(b_f)*a_f)-(func(a_f)*b_f))/(func(b_f)-func(a_f))
			k <- (a+b)/2
			Si func(k)*func(a)<0 Entonces
				b <- k
			SiNo
				a <- k
			FinSi
			Si func(a_f)*func(k_falso)<0 Entonces
				b_f <- k_falso
			SiNo
				a_f <- k_falso
			FinSi
			Si cont>1 Entonces
				err_ir <- abs((k-K_old)/k)
				err_ir_falso <- abs((k_falso-k_falso_old)/k_falso)
			FinSi
			k_falso_old <- k_falso
			K_old <- k
			cont <- cont+1
		FinMientras
	FinSi
	Escribir 'El contador llegó a: ', cont
	Escribir 'El valor obtenido para la raiz usando el metodo de biseccion es el siguiente: ', k, ', con un error de ', err_ir
	Escribir 'El valor obtenido para la raiz usando el metodo de falsa posicion el siguiente: ', k_falso, ', con un error de ', err_ir_falso
FinAlgoritmo

Función f <- func(value)
	Definir f Como Real
	f <- (value^10)-1
FinFunción
