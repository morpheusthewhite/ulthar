#ifndef MANDELBROT_H
#define MANDELBROT_H
#include <complex>
#include <QColor>

#define MANDELBROT_POWER    2

using namespace std;

typedef complex<double> Complex;

inline Complex calculateMandelbrot(Complex& z, Complex& c);

unsigned char calcultateMandelbrotTime(Complex& c);

#endif // MANDELBROT_H
