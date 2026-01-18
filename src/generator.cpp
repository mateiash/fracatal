#include <SDL2/SDL_surface.h>
#include <fstream>
#include <complex>
#include <string>

#include <SDL2/SDL.h>

#include "generator.h"

using namespace std::complex_literals;

void ViewGenerator::gen(SDL_Surface* surface){
    Uint32 *pixels = (Uint32 *)surface->pixels;
    int pitch = surface->pitch / 4;
    SDL_LockSurface(surface);

    GeneratorSettings settings = this->settings; 

    int W = settings.SIZE;
    int H = settings.SIZE;
    /*
    fout << "P3\n";
    fout << W << ' ' << H << '\n';
    fout << "255\n";
    */
    int ITERATIONS = settings.ITERATIONS;
    double BOUND = settings.BOUND;

    for (int r = 0; r < H; r++){
        for(int c = 0; c < W; c++){
            double x = ((double) (c - (double)W/2)) / ((double) W/2) * settings.SCALE + settings.CENTER_X;
            double y = ((double) ((double)H/2 - r)) / ((double) H/2) * settings.SCALE + settings.CENTER_Y;
            
            std::complex<double> c_ = x + y * 1i;
            std::complex<double> z = 0;

            int i;
            for(i = 0; i < ITERATIONS; i++){
                z = z*z + c_;
                if(abs(z) > BOUND){
                    break;
                }

            }

            uint8_t R = 0;
            uint8_t G = 255 * ((float) i / (float) ITERATIONS);
            uint8_t B = 0;
        
            R = G;
            B = G;

            Uint32 pixel = SDL_MapRGB(surface->format, R, G, B);
            pixels[r * pitch + c] = pixel;

            /*
            fout << R << ' ';
            fout << G << ' ';
            fout << B << "  ";
            */
        }
        //fout << '\n';
    }
    SDL_UnlockSurface(surface);

}