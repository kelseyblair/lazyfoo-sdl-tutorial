//
//  LButton.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-20.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef LButton_hpp
#define LButton_hpp

#include <SDL2/SDL.h>
#include "LButtonSprite.h"

//the mouse button
class LButton
{
public:
    //Initialized internal variables
    LButton();
    
    //Sets up left positions
    void setPosition( int x, int y );
    
    //Handles mouse event
    void handleEvent( SDL_Event* e );
    
    //Shows button sprite
    void render();
    
private:
    //Top left position
    SDL_Point mPosition;
    
    //Currently used global sprite
    LButtonSprite mCurrentSprite;
};



#endif /* LButton_hpp */
