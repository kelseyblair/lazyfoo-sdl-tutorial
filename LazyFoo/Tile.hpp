//
//  Tile.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-23.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef Tile_hpp
#define Tile_hpp

#include <SDL2/SDL.h>

class Tile
{
public:
    //Initializes position and type
    Tile( int x, int y, int tileType );
    
    //Shows the tile
    void render( SDL_Rect& camera );
    
    //Get the tile type
    int getType();
    
    //Get the collision box
    SDL_Rect getBox();
    
private:
    //The attributes of the tile
    SDL_Rect mBox;
    
    //The tile type
    int mType;
    
};

#endif /* Tile_hpp */
