//
//  LTexture.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-19.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef LTexture_hpp
#define LTexture_hpp

#include <SDL2/SDL.h>
#include <string>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>


//Texture wrapper class
class LTexture
{
public:
    //Initializes variables
    LTexture();
    
    //Deallocates memory
    ~LTexture();
    
    //Loades image at specified path
    bool loadFromFile( std::string path );
    
    #ifdef _SDL_TTF_H
    //Creates image from font strings
    bool loadFromRenderedText( std::string textureText, SDL_Color textColor );
    #endif
    
    //Deallocates texture
    void free();
    
    //Set color modulation
    void setColor( Uint8 red, Uint8 green, Uint8 blue );
    
    //Set blending
    void setBlendMode( SDL_BlendMode blending );
    
    //Set alpha modulation
    void setAlpha( Uint8 alpha );
    
    //Renders texture at given point
    void render( int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip Flip = SDL_FLIP_NONE );
    
    //Gets image dimensions
    int getWidth();
    int getHeight();
    
private:
    //The actual hardware texture
    SDL_Texture* mTexture;
    
    //Image dimensions
    int mWidth;
    int mHeight;
};

#endif /* LTexture_hpp */
