/*This source code copyrighted by Lazy Foo' Productions (2004-2022)
and may not be redistributed without written permission.*/

//Using SDL, SDL_image, standard IO, and strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <string>
#include "Texture.hpp"

#include <iostream>



//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 640;

const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
LTexture gFooTexture;
LTexture gBackgroundTexture;
LTexture gShlepaTexture;



bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial"
								  , SDL_WINDOWPOS_UNDEFINED
								  , SDL_WINDOWPOS_UNDEFINED
								  , SCREEN_WIDTH
								  , SCREEN_HEIGHT
								  , SDL_WINDOW_SHOWN );
		if( gWindow == NULL ) {
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED );
			if( gRenderer == NULL ) {
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			} else {
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
			}
		}
	}

	return success;
}

bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load Foo' texture
	if( !gFooTexture.loadFromFile( "./media/images/foo.png", gRenderer ) ) {
		printf( "Failed to load Foo' texture image!\n" );
		success = false;
	}
	
	//Load background texture
	if( !gBackgroundTexture.loadFromFile( "./media/images/background.png", gRenderer ) ) {
		printf( "Failed to load background texture image!\n" );
		success = false;
	}

	//Load Shlepa
	if( !gShlepaTexture.loadFromFile( "./media/images/shlepa.png", gRenderer ) ) {
		printf( "Failed to load Shlepa texture image!\n" );
		success = false;
	}

	return success;
}

void close() {
	//Free loaded images
	gFooTexture.free();
	gBackgroundTexture.free();

	//Destroy window	
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

int main( int argc, char* args[] ) {
	//Start up SDL and create window
	if( !init() ) {
		printf( "Failed to initialize!\n" );
	} else {
		//Load media
		if( !loadMedia() ) {
			printf( "Failed to load media!\n" );
		} else {	
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			int x{0};
			int y{0};
			int dx{0};
			int dy{0};
			int speed{3};
			const int max_speed{21};

			//While application is running
			while( !quit ) {
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 ) {
					//User requests quit
					if( e.type == SDL_QUIT ) {
						quit = true;
					} else if ( e.type == SDL_KEYDOWN ) {
						if(e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q) {
							quit = true;
						}
						switch(e.key.keysym.sym) {
							case SDLK_w:
							dy -= speed;
							break;

							case SDLK_s:
							dy += speed;
							break;
						}
						switch(e.key.keysym.sym) {
							case SDLK_a:
							dx -= speed;
							break;

							case SDLK_d:
							dx += speed;
							break;
						}
					}
				}

				

				if (dy > max_speed) {
					dy = max_speed;
				} else if (dy < - max_speed) {
					dy = -max_speed;
				}

				if (dx > max_speed) {
					dx = max_speed;
				} else if (dx < - max_speed) {
					dx = -max_speed;
				}

				if ( x < 0 || SCREEN_WIDTH < x || y < 0 || SCREEN_HEIGHT < y ) {
					dx = 0;
					dy = 0;
				}

				if ( x < 0 ) {
					x = 0;	
				}

				if ( SCREEN_WIDTH <= x + gShlepaTexture.getWidth() ) {
					x =  SCREEN_WIDTH - gShlepaTexture.getWidth(); 
				}

				if ( y < 0 ) {
					y = 0;	
				}

				if ( SCREEN_HEIGHT <= y + gShlepaTexture.getHeight()) {
					y = SCREEN_HEIGHT - gShlepaTexture.getHeight();	
				}

				x += dx;
				y += dy;

				
				std::cout << "l r: " << x << ' ' << x + gShlepaTexture.getWidth() << '\n' <<
							 "t b: " << y << ' ' << y + gShlepaTexture.getHeight() << '\n' <<
							 "w h: " << gShlepaTexture.getWidth() << ' ' << gShlepaTexture.getHeight() << '\n' <<
							 "W H: " << SCREEN_WIDTH << ' ' << SCREEN_HEIGHT << '\n' <<
							 "W <= l + h >> " << (SCREEN_WIDTH <= x + gShlepaTexture.getWidth()) << "\n\n";

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background texture to screen
				gBackgroundTexture.render( 0, 0, gRenderer );

				//Render Foo' to the screen
				gFooTexture.render( 240, 190, gRenderer );

				//Render Shlepa texture to screen
				gShlepaTexture.render(x, y, gRenderer);

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}
