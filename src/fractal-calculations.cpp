#include "mandelbrot.h"
#include "fractal-calculations.h"

void calculateFractal(unsigned int horizontalSteps, unsigned int verticalSteps,
                     double stepSize, unsigned int threadIndex,
                     unsigned int nThreads, unsigned char *pixelArray,
                      double starting_real, double ending_img){

    unsigned int start = (verticalSteps/nThreads) * threadIndex;
    /* avoiding errors in the last approximation */
    unsigned int end = (threadIndex != nThreads - 1)? (verticalSteps/nThreads) * (threadIndex+1) : verticalSteps;

    /* iterating over each pixel */
    unsigned int a, b;

    for(b=start; b<end; b++){ // iterating over imaginary values
        for(a=0; a<horizontalSteps; a++){ // iterating over real values
            Complex c(starting_real + a * stepSize, ending_img - b * stepSize);

            /* calculating time of the given complex number */
            unsigned char mandelbrotTime = calcultateMandelbrotTime(c);

            /* saving it in the allocated array */
            pixelArray[b * horizontalSteps + a] = mandelbrotTime;
        }

    }
}

/* Maps a certain unsigned char (or int) to a QColor */
void charToColor(QColor &qColor, unsigned char t1){
//    unsigned char zero = 0;

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

    qColor.setRgb(resR, resG, resB);

    return;
}

