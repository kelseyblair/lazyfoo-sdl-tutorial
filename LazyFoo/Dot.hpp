//
//  Dot.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-20.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef Dot_hpp
#define Dot_hpp

#include <SDL2/SDL.h>
#include <vector>

#include "Circle.h"
#include "Particle.hpp"
#include "Tile.hpp"


//The dot that will move around the screen
class Dot
{
public:
    //The dimensions of the dot
    static const int DOT_WIDTH = 20;
    static const int DOT_HEIGHT = 20;
    
    //Maximum axis velosicty of the dot
    static const int DOT_VEL = 10;
    
    //Initializes the variables
    Dot();
    
    //Deallocates particle
    ~Dot();
    
    //Takes key presses and adjusts the dot's velocity
    void handleEvent( SDL_Event& e );
    
    //Moves the dot and checks collision against tiles
    void move( Tile *tiles[] );
    
    //Centers the camera over the dot
    void setCamera( SDL_Rect& camera );
    
    //Shows the dot on the screen
    void render( SDL_Rect& camera );
//    void render( int camX, int camY );

    //Position accessors
    int getPosX();
    int getPosY();
//
//    //Gets the collision boxed
//    Circle& getCollider();
    
private:
    //The particles
    Particle* particles[ 20 ]; //TOTAL_PARTICLES
    
    //Collision box of the dot
    SDL_Rect mBox;
    
    //Shows the particles
    void renderParticles();
    
    //The X and Y offsets of the dot
    int mPosX, mPosY;
    
    //The velocity of the dot
    int mVelX, mVelY;
//    
//    //Dot's collision box
//    Circle mCollider;
//    
//    //Moves the collision boxes relative to the dot's offset
//    void shiftColliders();
    
};

#endif /* Dot_hpp */
