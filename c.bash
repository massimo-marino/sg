#!/bin/bash
clang++ -std=c++17 \
        -stdlib=libc++ \
        -Ofast -ffast-math \
        -Wall -Weffc++ -Wextra -Wfatal-errors -Weverything -pedantic-errors \
        -Wno-c++98-compat -Wno-c++98-compat-pedantic \
        -fno-assume-sane-operator-new \
        -pthread \
        -I/clang_7.0.0/include/c++/v1 -I. \
        main.cpp helpers.cpp rgb.cpp palette.cpp ppm.cpp bmp.cpp \
        perlinNoise.cpp perlinDemos.cpp \
        -mtune=native -march=native -m64 \
        -o sg \
        -lm -lrt
