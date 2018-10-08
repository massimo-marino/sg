#!/bin/bash
clang++ -std=c++17 -Ofast -ffast-math -stdlib=libc++ -pedantic-errors -Wall -Weffc++ -Wextra -Wfatal-errors -Weverything -Wno-c++98-compat -Wno-c++98-compat-pedantic -pthread main.cpp helpers.cpp rgb.cpp palette.cpp perlinDemos.cpp ppm.cpp perlinNoise.cpp -o sg -lm -lrt
