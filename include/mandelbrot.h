#ifndef MANDELBROT_H
#define MANDELBROT_H
#include <complex>
#include <QColor>

#define LOWEST_I            -2
#define LOWEST_R            -2
#define BIGGEST_I           2
#define BIGGEST_R           2
#define MANDELBROT_POWER    2
#define STEPS               1000

#define T1   0
#define T2   1

#define A_R  255
#define A_G  39
#define A_B  62

#define B_R  0
#define B_G  0
#define B_B  0
//#define B_R  116
//#define B_G  167
//#define B_B  204

using namespace std;

typedef complex<double> Complex;

inline Complex calculateMandelbrot(Complex& z, Complex& c);

unsigned char calcultateMandelbrotTime(Complex& c);

void charToColor(QColor &qColor, unsigned char t);

#endif // MANDELBROT_H
