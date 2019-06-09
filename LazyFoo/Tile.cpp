//
//  Tile.cpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-23.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#include "Tile.hpp"

#include "program.h"
#include "TileSprites.h"

Tile::Tile( int x, int y, int tileType )
{
    //Set the offsets
    mBox.x = x;
    mBox.y = y;
    
    //Set the collision box
    mBox.w = TILE_WIDTH;
    mBox.h = TILE_HEIGHT;
    
    //Get the tile type
    mType = tileType;
}

void Tile::render( SDL_Rect& camera )
{
    //If the tile is on screen
    if( checkCollision( camera, mBox ) )
    {
        //Show the tile
        gTileTexture.render( ( mBox.x - camera.x ), ( mBox.y - camera.y ), &gTileClips[ mType ] );
    }
}

int Tile::getType()
{
    return mType;
}

SDL_Rect Tile::getBox()
{
    return mBox;
}