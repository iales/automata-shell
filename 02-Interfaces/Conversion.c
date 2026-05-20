#include "Conversion.h"

double Celsius(double f)
{
  return (f - 32) * 5.0 / 9.0;
}

double Fahrenheit(double c)
{
  return c * 9.0 / 5.0 + 32;
}