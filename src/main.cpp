#include <iostream>
#include <fstream>
#include <QImage>
#include <thread>
#include <chrono>
#include "mandelbrot.h"
#include "fractal-calculations.h"

#define OUTPUT_FILENAME     "out.jpeg"
#define IMAGE_QUALITY       100

#define LOWEST_I            -2
#define LOWEST_R            -2
#define BIGGEST_I           2
#define BIGGEST_R           2

#define STEPS               500

using namespace std;


bool produceOutput(unsigned char* data, unsigned int rows, unsigned int cols){
    QImage outputImage(static_cast<int>(cols),
                       static_cast<int>(rows),
                       QImage::Format_RGB32);

    unsigned int a, b;

    QColor qColor;
    for(b=0; b<rows; b++){
        for(a=0; a<cols; a++){
            unsigned char color = (data[a + b*cols]);
            charToColor(qColor, color);
            outputImage.setPixelColor(static_cast<int>(a),
                                      static_cast<int>(b),
                                      qColor);
        }
    }

    QString outputFilename(OUTPUT_FILENAME);

    return outputImage.save(outputFilename, "jpeg", IMAGE_QUALITY);
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
        threads[i] = thread(calculateFractal, horizontalSteps, verticalSteps,
                            stepSize, i, concurentThreadsSupported, pixels,
                            LOWEST_R, BIGGEST_I);

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
