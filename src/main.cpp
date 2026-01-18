#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keycode.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_timer.h>
#include <iostream>

#include <SDL2/SDL.h>

#include "generator.h"

const std::string PROGRAM_NAME = "Fracatal";

const int WIN_SIZE = 720;

int main(int argc, char** args){
    // mandelbrot se selecteaza un nr complex c
    // z_k = z_k-1^2 + c
    // z_0 = 0
    // daca z tinde la infinit nr nu este in multime

    // Pointers to our window and surface
	SDL_Surface* winSurface = NULL;
	SDL_Window* window = NULL;

	// Initialize SDL. SDL_Init will return -1 if it fails.
	if ( SDL_Init( SDL_INIT_EVERYTHING ) < 0 ) {
		std::cout << "Error initializing SDL: " << SDL_GetError() << '\n';
		system("pause");
		// End the program
		return 1;
	} 

	// Create our window
	window = SDL_CreateWindow( PROGRAM_NAME.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIN_SIZE, WIN_SIZE, SDL_WINDOW_SHOWN );

    // Make sure creating the window succeeded
	if ( !window ) {
		std::cout << "Error creating window: " << SDL_GetError()  << '\n';
		system("pause");
		// End the program
		return 1;
	}

	// Get the surface from the window
	winSurface = SDL_GetWindowSurface( window );

	// Make sure getting the surface succeeded
	if ( !winSurface ) {
		std::cout << "Error getting surface: " << SDL_GetError() << '\n';
		system("pause");
		// End the program
		return 1;
	}

    // rendering shit yeah lets go

	GeneratorSettings saved1;
    saved1.SCALE = 1;
    saved1.CENTER_X = 0.;
    saved1.CENTER_Y = 0.;
    saved1.SIZE = 256;
    saved1.ITERATIONS = 128;
    saved1.BOUND = 4;

    ViewGenerator generator(saved1);

	SDL_Rect dest;
	dest.x = 0;
	dest.y = 0;
	dest.w = WIN_SIZE;
	dest.h = WIN_SIZE;

	SDL_Surface *view = SDL_CreateRGBSurfaceWithFormat(
		0,
		generator.settings.SIZE,
		generator.settings.SIZE,
		32,
		SDL_PIXELFORMAT_ARGB8888
	);
	double adder = 0.1;
	SDL_Event ev;
	int running = 1;
	generator.gen(view);
	SDL_BlitScaled(view, NULL, winSurface, &dest);
	while(running){
		if(SDL_PollEvent(&ev) != 0){
			if(ev.type == SDL_QUIT){
				running = 0;
			}
			if(ev.type == SDL_KEYDOWN){
				switch(ev.key.keysym.sym){
					case SDLK_UP:
						generator.settings.SCALE *= 0.9;
						break;
					case SDLK_DOWN:
						generator.settings.SCALE /= 0.9;
						break;
					case SDLK_d:
						generator.settings.CENTER_X += adder*generator.settings.SCALE;
						break;
					case SDLK_w:
						generator.settings.CENTER_Y += adder*generator.settings.SCALE;
						break;
					case SDLK_a:
						generator.settings.CENTER_X -= adder*generator.settings.SCALE;
						break;
					case SDLK_s:
						generator.settings.CENTER_Y -= adder*generator.settings.SCALE;
						break;
					case SDLK_r:
						generator.settings = saved1;
						break;
					case SDLK_SPACE:
						int result = SDL_SaveBMP(view, "screenshot.bmp");
						break;
				}
				generator.gen(view);
				//SDL_Delay(100);
				SDL_BlitScaled(view, NULL, winSurface, &dest);
			}
		}
		
		SDL_UpdateWindowSurface( window );
	}


	SDL_DestroyWindow( window );

	SDL_Quit();


    /*
    GeneratorSettings saved1;
    saved1.SCALE = 0.032;
    saved1.CENTER_X = 0.424;
    saved1.CENTER_Y = 0.335;
    saved1.SIZE = 1024;
    saved1.ITERATIONS = 256;
    saved1.BOUND = 4;

    std::cout << "Generating!\n";

    ViewGenerator generator;
    generator.settings = saved1;

    generator.gen("o.ppm");

    std::cout << "Generated!\n";
    */
    return 0;
}