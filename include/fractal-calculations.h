#ifndef FRACTALCALCULATOR_H
#define FRACTALCALCULATOR_H
#include <QColor>

#define T1   0
#define T2   1

#define A_R  255
#define A_G  39
#define A_B  62

#define B_R  0
#define B_G  0
#define B_B  0

void calculateFractal(unsigned int horizontalSteps, unsigned int verticalSteps,
                     double stepSize, unsigned int threadIndex,
                     unsigned int nThreads, unsigned char *pixelArray,
                      double starting_real, double ending_img);

void charToColor(QColor &qColor, unsigned char t);

#endif // FRACTALCALCULATOR_H
