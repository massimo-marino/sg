#!/bin/bash
clang++ -std=c++17 \
        -stdlib=libc++ \
        -Ofast -ffast-math \
        -pedantic-errors -Wall -Weffc++ -Wextra -Wfatal-errors -Weverything \
        -Wno-c++98-compat -Wno-c++98-compat-pedantic \
        -fno-assume-sane-operator-new \
        -pthread \
        -I/clang_7.0.0/include/c++/v1 -I. \
        main.cpp ppm.cpp perlinNoise.cpp perlinDemos.cpp helpers.cpp rgb.cpp \
        palette.cpp bmp.cpp \
        -mtune=native -march=native -m64 \
        -o sg \
        -lm -lrt

