#include <QImage>
#include "mandelbrot.h"
#include <cmath>

inline Complex calculateMandelbrot(Complex& z, Complex& c){
    Complex resultPower = pow(z, MANDELBROT_POWER);
    Complex resultSum(resultPower.real() + c.real(),
                      resultPower.imag() + c.imag());

    return resultSum;
}

unsigned char calcultateMandelbrotTime(Complex& c){
    unsigned char iterations = 0;

    Complex z(c);

    while(iterations < 255){
        if(abs(z) > 2) break;
        else {
            z = calculateMandelbrot(z, c);
            iterations++;
        }
    }

    return iterations;
}

