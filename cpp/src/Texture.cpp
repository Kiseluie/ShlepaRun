#include "Texture.hpp"
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

LTexture::LTexture() {
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture() {
	//Deallocate
	free();
}

bool LTexture::loadFromFile( const std::string path, SDL_Renderer* renderer ) {
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s!"
				" SDL_image Error: %s\n"
			  , path.c_str()
			  , IMG_GetError() );
	} else {
		//Color key image
		SDL_SetColorKey( loadedSurface
					   , SDL_TRUE
					   , SDL_MapRGB( loadedSurface->format, 0, 0xFF, 0xFF ) );

		//Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
		if( newTexture == NULL ) {
			printf( "Unable to create texture from %s!"
					" SDL Error: %s\n"
				  , path.c_str()
				  , SDL_GetError() );
		} else {
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface( loadedSurface );
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

void LTexture::free() {
	//Free texture if it exists
	if( mTexture != NULL ) {
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::render( const int& x, const int& y, SDL_Renderer* renderer ) {
	//Set rendering space and render to screen
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	SDL_RenderCopy( renderer, mTexture, NULL, &renderQuad );
}

int LTexture::getWidth() {
	return mWidth;
}

int LTexture::getHeight() {
	return mHeight;
}
