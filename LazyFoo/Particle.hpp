//
//  Particle.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-22.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef Particle_hpp
#define Particle_hpp

#include "LTexture.hpp"

class Particle
{
public:
    //Initialize position and animation
    Particle( int x, int y);
    
    //Shows the particle
    void render();
    
    //Checks if particle is dead
    bool isDead();
    
private:
    //Offsets
    int mPosX, mPosY;
    
    //Current frame of animation
    int mFrame;
    
    //Type of particle
    LTexture *mTexture;
};

#endif /* Particle_hpp */
