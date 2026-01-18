#pragma once
#include <SDL2/SDL_surface.h>
#include <string>

#include <SDL2/SDL.h>

struct GeneratorSettings{
    double SCALE;
    double CENTER_X;
    double CENTER_Y;

    double SIZE;

    int ITERATIONS;
    double BOUND;
};

class ViewGenerator {
    public:
        GeneratorSettings settings;

        void gen(SDL_Surface* surface);
};