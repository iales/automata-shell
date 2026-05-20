#include "Conversion.h"
#include <stdio.h>

void PrintTablas(int lower, int upper, int step);
void PrintTablaCelsius(int lower, int upper, int step);
void PrintTablaFahrenheit(int lower, int upper, int step);
void PrintFilas(int lower, int upper, int step, double (*Conversion)(double));
void PrintFila(int valor, double resultado);

void PrintTablas(int lower, int upper, int step)
{
    PrintTablaCelsius(lower, upper, step);
    PrintTablaFahrenheit(lower, upper, step);
}

void PrintTablaCelsius(int lower, int upper, int step)
{
    printf("\n|%10s|%11s|\n", "Celsius", "Fahrenheit");
    PrintFilas(lower, upper, step, Fahrenheit);
}

void PrintTablaFahrenheit(int lower, int upper, int step)
{
    printf("\n|%10s|%11s|\n", "Fahrenheit", "Celsius");
    PrintFilas(lower, upper, step, Celsius);
}

void PrintFilas(int lower, int upper, int step, double (*Conversion)(double))
{
    for (int valor = lower; valor <= upper; valor += step)
    {
        PrintFila(valor, Conversion(valor));
    }
}

void PrintFila(int valor, double resultado)
{
    printf("|%10d|%11.2f|\n", valor, resultado);
}

int main()
{
    const int lower = 0;
    const int upper = 300;
    const int step = 20;

    PrintTablas(lower, upper, step);
    return 0;
}
