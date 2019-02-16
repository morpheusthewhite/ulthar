# Created by and for Qt Creator This file was created for editing the project sources only.
# You may attempt to use it for building too, by modifying this file here.

QT += widgets core gui

HEADERS = \
    include/mandelbrot.h \
    include/fractal-calculations.h \
    include/cxxopts.hpp \
    include/gui.h

SOURCES = \
   $$PWD/src/main.cpp \
    $$PWD/src/mandelbrot.cpp \
    src/fractal-calculations.cpp \
    src/gui.cpp

INCLUDEPATH = include/

CONFIG += optimize_full

