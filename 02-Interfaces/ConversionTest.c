#include "Conversion.h"
#include <assert.h>
#include <math.h>

int AreNear(double a, double b, double tolerance) {
    return fabs(a - b) <= tolerance;
}

int main()
{

    assert(AreNear(Celsius(-40), -40, 0.1));
    assert(AreNear(Fahrenheit(-40), -40, 0.1));

    assert(AreNear(Celsius(14), -10, 0.1));
    assert(AreNear(Fahrenheit(-10), 14, 0.1));

    assert(AreNear(Celsius(32), 0, 0.1));
    assert(AreNear(Fahrenheit(0), 32, 0.1));

    assert(AreNear(Celsius(50), 10, 0.1));
    assert(AreNear(Fahrenheit(10), 50, 0.1));

    assert(AreNear(Celsius(74), 23.3, 0.1));
    assert(AreNear(Fahrenheit(23.3), 74, 0.1));

    assert(AreNear(Celsius(89.6), 32, 0.1));
    assert(AreNear(Fahrenheit(32), 89.6, 0.1));

    assert(AreNear(Celsius(98.6), 37.0, 0.1));
    assert(AreNear(Fahrenheit(37.0), 98.6, 0.1));

    assert(AreNear(Celsius(122), 50, 0.1));
    assert(AreNear(Fahrenheit(50), 122, 0.1));

    assert(AreNear(Celsius(158), 70, 0.1));
    assert(AreNear(Fahrenheit(70), 158, 0.1));

    assert(AreNear(Celsius(212), 100.0, 0.1));
    assert(AreNear(Fahrenheit(100.0), 212.0, 0.1));

}


