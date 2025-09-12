cmake_minimum_required(VERSION 4.0)
project(Métodos_Numéricos C)

set(CMAKE_C_STANDARD 11)

add_executable(Métodos_Numéricos
        Semana1/hola_dci.c
        Semana2/Ago12_ej1.c
        Semana2/operaciones_float.c
        Semana2/operaciones_int.c
        "Semana2/Serie mclaurin.c"
        "Semana3/Serie mclaurin.c"
        Semana4/codigo_taylor.c
        Semana4/taylor.c
        Tareas/Codigo_derivadas_Taylor.c
        Tareas/formula_general1.c
        Tareas/serie_de_taylor.c
        Tareas/Tarea13_Agosto_2025.c
        Semana6/ejercicio_clase_errores.c)
