#include <iostream>
#include <fstream>
#include <QImage>
#include <thread>
#include <chrono>
#include "mandelbrot.h"

#define OUTPUT_FILENAME     "out.jpeg"
#define IMAGE_QUALITY       100

using namespace std;


bool produceOutput(unsigned char* data, unsigned int rows, unsigned int cols){
    QImage outputImage(cols, rows, QImage::Format_RGB32);

    unsigned int a, b;

    QColor qColor;
    for(b=0; b<rows; b++){
        for(a=0; a<cols; a++){
            char color = (data[a + b*cols]);
            charToColor(qColor, color);
            outputImage.setPixelColor(a, b, qColor);
        }
    }

    QString outputFilename(OUTPUT_FILENAME);

    return outputImage.save(outputFilename, "jpeg", IMAGE_QUALITY);
}


void calculatePixels(unsigned int horizontalSteps, unsigned int verticalSteps,
                     double stepSize, unsigned int threadIndex,
                     unsigned int nThreads, unsigned char *pixelArray){

    unsigned int start = (verticalSteps/nThreads) * threadIndex;
    /* avoiding errors in the last approximation */
    unsigned int end = (threadIndex != nThreads - 1)? (verticalSteps/nThreads) * (threadIndex+1) : verticalSteps;

    /* iterating over each pixel */
    unsigned int a, b;

    for(b=start; b<end; b++){ // iterating over imaginary values
        for(a=0; a<horizontalSteps; a++){ // iterating over real values
            Complex c(LOWEST_R + a * stepSize, BIGGEST_I - b * stepSize);

            /* calculating time of the given complex number */
            unsigned char mandelbrotTime = calcultateMandelbrotTime(c);

            /* saving it in the allocated array */
            pixelArray[b * horizontalSteps + a] = mandelbrotTime;
        }

    }
}


int main(){
    /* calculating the cartesian width and height of the image */
    double width = BIGGEST_R - LOWEST_R;
    double height = BIGGEST_I - LOWEST_I;

    /* calculating the number of horizontal and vertical pixels */
    unsigned int horizontalSteps = width * STEPS;
    unsigned int verticalSteps = height * STEPS;

    /* debug prints */
    cout << "horizontalSteps: " << horizontalSteps << endl;
    cout << "verticalSteps: " << verticalSteps << endl;

    /* allocating needed array */
    unsigned char* pixels = new (nothrow) unsigned char[horizontalSteps * verticalSteps];
    
    /* the cartesian distance between each pixel */
    double stepSize = 1 / static_cast<double>(STEPS);

    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();

    unsigned concurentThreadsSupported = thread::hardware_concurrency();

    /* Sets available threads to 1 if call was not supported (returned 0) */
    concurentThreadsSupported = concurentThreadsSupported == 0 ? 1 : concurentThreadsSupported;

    cout << "Launching " << concurentThreadsSupported << " threads!"<< endl;

    unsigned int i;
    thread* threads = new thread [concurentThreadsSupported];

    /* launching threads */
    for(i=0; i<concurentThreadsSupported; i++)
        threads[i] = thread(calculatePixels, horizontalSteps, verticalSteps, stepSize, i, concurentThreadsSupported, pixels);

    /* waiting for threads to terminate */
    for(i=0; i<concurentThreadsSupported; i++)
        threads[i].join();

    delete[] threads;

    chrono::time_point<chrono::high_resolution_clock> end = chrono::high_resolution_clock::now();
    cout << "Time to calculate bitmap: " << chrono::duration_cast<chrono::microseconds>(end - start).count()/1000000. << endl << endl;

    /* outputting in a JPEG*/
    if(produceOutput(pixels, verticalSteps, horizontalSteps)) cout << "Image correctly saved!" << endl;
    else cout << "Image saving failed!" << endl;

    /* freeing memory */
    delete[] pixels;

    return 0;
}
