#include <iostream>
#include <fstream>
#include <QImage>
#include <thread>
#include <chrono>
#include <QApplication>
#include <assert.h>

#include "cxxopts.hpp"
#include "mandelbrot.h"
#include "fractal-calculations.h"
#include "gui.h"

#define OUTPUT_FILENAME     "out.jpeg"
#define IMAGE_QUALITY       100

#define LOWEST_I            -2
#define LOWEST_R            -2
#define BIGGEST_I           2
#define BIGGEST_R           2

#define STEPS               500

#define DEBUG               1

using namespace std;


bool produceOutput(unsigned char* data, unsigned int rows, unsigned int cols,
                   string outputFilenameString, unsigned int quality){
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

    QString outputFilename = QString::fromStdString(outputFilenameString);

    return outputImage.save(outputFilename, "jpeg", quality);
}



cxxopts::Options* initializeParser(){
    // allocates the parser
    cxxopts::Options* options = new cxxopts::Options("Ulthar", "a fancy fractal generator");

    // adding parsing parameters
    options->add_options()
      ("h,help", "Shows info about Ulthar")
      ("c,cli", "Run on command line")
      ("q,quality", "Output image quality", cxxopts::value<unsigned int>()->default_value("100"))
      ("d,definition", "Definition of the output image (number of pixels in each cartesian unit)",
                    cxxopts::value<unsigned int>()->default_value("100"))
      ("f,file", "Output filename (.jpg or .jpeg)", cxxopts::value<string>()->default_value("out.jpeg"))
      ;

    return options;
}


void runOnCli(cxxopts::ParseResult parsedResults){

    // parsing all options
    string outputFilename = parsedResults["file"].as<string>();
    unsigned int quality = parsedResults["quality"].as<unsigned int>();
    quality = quality > 100 ? 100 : quality;
    unsigned int definition = parsedResults["definition"].as<unsigned int>();

    /* calculating the cartesian width and height of the image */
    double width = BIGGEST_R - LOWEST_R;
    double height = BIGGEST_I - LOWEST_I;

    /* calculating the number of horizontal and vertical pixels */
    unsigned int horizontalSteps = width * definition;
    unsigned int verticalSteps = height * definition;
    /* the cartesian distance between each pixel */
    double stepSize = 1 / definition;

    /* debug prints */
    if(DEBUG){
        cout << "horizontalSteps: " << horizontalSteps << endl;
        cout << "verticalSteps: " << verticalSteps << endl;
    }

    /* allocating needed array */
    unsigned char* pixels = new (nothrow) unsigned char[horizontalSteps * verticalSteps];


    chrono::time_point<chrono::high_resolution_clock> start = chrono::high_resolution_clock::now();

    unsigned concurentThreadsSupported = thread::hardware_concurrency();
    /* Sets available threads to 1 if call was not supported (returned 0) */
    concurentThreadsSupported = concurentThreadsSupported == 0 ? 1 : concurentThreadsSupported;
    cout << "Launching " << concurentThreadsSupported << " threads!"<< endl;
    thread* threads = new thread [concurentThreadsSupported];

    /* launching threads */
    unsigned int i;
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
    if(produceOutput(pixels, verticalSteps, horizontalSteps, outputFilename, quality)) cout << "Image correctly saved!" << endl;
    else cout << "Image saving failed!" << endl;

    /* freeing memory */
    delete[] pixels;

}

void runGui(int argc, char** argv){
    QApplication app(argc, argv);

    Gui gui(nullptr);
    gui.show();

    app.exec();
}

int main(int argc, char** argv){
    // parsing command line
    auto parser = initializeParser();
    assert(parser && "Parser is null");

    cxxopts::ParseResult result = parser->parse(argc, argv);

    if(result.count("help")) {
        // printing help and exiting
        cout << parser->help() << endl;
        return 0;
    }
    else if(result.count("cli")) runOnCli(result);
    else runGui(argc, argv);

    delete parser;
    return 0;
}
