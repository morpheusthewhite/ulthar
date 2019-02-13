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

/* Maps a certain unsigned char (or int) to a QColor */
void charToColor(QColor &qColor, unsigned char t1){
    unsigned char zero = 0;

    double t = static_cast<double>(1) / t1;

    unsigned char resR, resG, resB;
    if(t < T1){
        resR = A_R; resG = A_G; resB = A_B;
    }
    else if(t > T2){
        resR = B_R; resG = B_G; resB = B_B;
    }
    else {
        resR = B_R * (t - T1) + A_R * (T2 - t);
        resG = B_G * (t - T1) + A_G * (T2 - t);
        resB = B_B * (t - T1) + A_B * (T2 - t);
    }


//    resR = max(zero, resR);
//    resG = max(zero, resG);
//    resB = max(zero, resB);

    qColor.setRgb(resR, resG, resB);

    return;
}

