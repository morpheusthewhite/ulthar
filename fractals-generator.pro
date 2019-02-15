# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

#TARGET = mandelbrot

HEADERS = \
    include/mandelbrot.h \
    include/fractal-calculations.h \
    include/cxxopts.hpp

SOURCES = \
   $$PWD/src/main.cpp \
    $$PWD/src/mandelbrot.cpp \
    src/fractal-calculations.cpp

INCLUDEPATH = include/

CONFIG += optimize_full

