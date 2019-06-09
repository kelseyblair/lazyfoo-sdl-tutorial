//
//  program.cpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-19.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#include "program.h"


// GLOBAL VARIABLES
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_FPS = 60;
const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

const int LEVEL_WIDTH = 1280;
const int LEVEL_HEIGHT = 960;

const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
const int TOTAL_BUTTONS = 4;

const int TOTAL_DATA = 10;

const int TOTAL_PARTICLES = 20;

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int TOTAL_TILES = 192;

SDL_Renderer* gRenderer = NULL;
//LWindow gWindow;
SDL_Window* gWindow = NULL;
int gTotalDisplays = 0;
SDL_Rect* gDisplayBounds;

LTexture gSceneTexture;

TTF_Font* gFont = NULL;

LTexture gButtonSpriteSheetTexture;
SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];

LTexture gBackgroundTexture;

LTexture gPromptTextTexture;

LTexture gDotTexture;

LTexture gRedTexture;
LTexture gGreenTexture;
LTexture gBlueTexture;
LTexture gShimmerTexture;

LTexture gTileTexture;
SDL_Rect gTileClips[ TOTAL_TILE_SPRITES ];

bool init()
{
    //Initialization flag
    bool success = true;
    
    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        //Get number of displays
        gTotalDisplays = SDL_GetNumVideoDisplays();
        if( gTotalDisplays < 2 )
        {
            printf( "Only one display connected!\n" );
        }
        
        //Get bounds of each display
        gDisplayBounds = new SDL_Rect[ gTotalDisplays ];
        for( int i = 0; i < gTotalDisplays; ++i )
        {
            SDL_GetDisplayBounds( i, &gDisplayBounds[ i ] );
        }
        
        //Create window
        gWindow = SDL_CreateWindow( "SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
//        if( !gWindow.init() )
        {
            printf( "Window could not be created!\n" );
            success = false;
        }
        else
        {
            //Create renderer for window
//            gRenderer = gWindow.createRenderer();
            gRenderer = SDL_CreateRenderer( gWindow, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
                
                //Initialize SDL_mixer
                if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
                {
                    printf( "SDL_mixer could not initialze! SDL_mixer Errer: %s\n", Mix_GetError() );
                    success = false;
                }
                
                #ifdef _SDL_TTF_H
                //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }
                #endif
            }
        }
    }
    
    return success;
}

bool loadMedia( Tile* tiles[] )
{
    //Loading success flag
    bool success = true;
    
//    if( !gSceneTexture.loadFromFile( "window.png" ) )
//    {
//        printf( "Could not load window texture!\n" );
//        success = false;
//    }

    //Load dot texture
    if( !gDotTexture.loadFromFile( "dot.bmp") )
    {
        printf( " Failed to load dot texture!\n" );
        success = false;
    }
    if( !gRedTexture.loadFromFile( "red.bmp") )
    {
        printf( " Failed to load red texture!\n" );
        success = false;
    }
    if( !gGreenTexture.loadFromFile( "green.bmp") )
    {
        printf( " Failed to load green texture!\n" );
        success = false;
    }
    if( !gBlueTexture.loadFromFile( "blue.bmp") )
    {
        printf( " Failed to load blue texture!\n" );
        success = false;
    }
    if( !gShimmerTexture.loadFromFile( "shimmer.bmp") )
    {
        printf( " Failed to load shimmer texture!\n" );
        success = false;
    }
    
    //Set texture transparency
    gRedTexture.setAlpha( 192 );
    gGreenTexture.setAlpha( 192 );
    gBlueTexture.setAlpha( 192 );
    gShimmerTexture.setAlpha( 192 );
    
    //Load tile texture
    if( !gTileTexture.loadFromFile( "tiles.png" ) )
    {
        printf(" Failed to load tile set texture!\n" );
        success = false;
    }
    
    //Load tile map
    if( !setTiles( tiles ) )
    {
        printf( "Failed to load tile set!\n" );
        success = false;
    }
    
    return success;
}

void close( Tile* tiles[] )
{
    //Deallocate tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        if( tiles[i] == NULL )
        {
            delete tiles[i];
            tiles[i] = NULL;
        }
    }
    
    //Free loaded images
    gButtonSpriteSheetTexture.free();
    gDotTexture.free();
    gBackgroundTexture.free();
    gPromptTextTexture.free();
    gTileTexture.free();
    
    #ifdef _SDL_TTF_H
    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;
    #endif
    
    SDL_DestroyRenderer( gRenderer );
    SDL_DestroyWindow( gWindow );
//    gWindow.free();
    gWindow = NULL;
    gRenderer = NULL;
    
    //Quit SDL subsystems
    #ifdef _SDL_TTF_H
    TTF_Quit();
    #endif
    Mix_Quit();
    IMG_Quit();
    SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b)
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;
    
    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;
    
    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;
    
    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }
    
    if( topA >= bottomB )
    {
        return false;
    }
    
    if( rightA <= leftB )
    {
        return false;
    }
    
    if( leftA >= rightB )
    {
        return false;
    }
    
    //If none of the sides from A are outside B
    return true;
}

bool touchesWall( SDL_Rect box, Tile* tiles[] )
{
    //go through the tiles
    for( int i = 0; i < TOTAL_TILES; ++i )
    {
        //If the tile is a wall type tile
        if( ( tiles[ i ]->getType() >= TILE_CENTER ) && ( tiles[ i ]->getType() <= TILE_TOPLEFT ) )
        {
            //If the collision box touches the wall tile
            if( checkCollision( box, tiles[ i ]->getBox() ) )
            {
                return true;
            }
        }
    }
    
    //If no wall tiles were touched
    return false;
}

bool setTiles( Tile* tiles[] )
{
    //Success flag
    bool tilesLoaded = true;
    
    //The tile offsets
    int x = 0, y = 0;
    
    //Open the map
    std::ifstream map( "lazy.map" );
    
    //If the map couldn't be loaded
    if( !map.is_open() )
    {
        printf( "Unable to load map file!\n" );
        tilesLoaded = false;
    }
    else
    {
        //Initialize the tiles
        for( int i = 0; i < TOTAL_TILES; ++i )
        {
            //Determines what kind of tile will be made
            int tileType = -1;
            
            //Read tile from map file
            map >> tileType;
            
            //If there was a problem in reading the map
            if( map.fail() )
            {
                //Stop loading map
                printf( "Error loading map: Unexpected end of file!\n" );
                tilesLoaded = false;
                break;
            }
            
            //If the number is a valid tile number
            if( ( tileType >= 0 ) && ( tileType < TOTAL_TILE_SPRITES ) )
            {
                tiles[ i ] = new Tile( x, y, tileType );
            }
            //If we don't recognize the tile type
            else
            {
                //Stop loading map
                printf( "Error loading map: Invalid tile type at %d!\n", i );
                tilesLoaded = false;
                break;
            }
            //Move to the next tile spot
            x += TILE_WIDTH;
            
            //If we've gone too far
            if( x >= LEVEL_WIDTH )
            {
                //Move back
                x = 0;
                
                //Move to the next row
                y += TILE_HEIGHT;
            }
            
        }
        
        //Clip the sprite sheet
        if( tilesLoaded )
        {
            gTileClips[ TILE_RED ].x = 0;
            gTileClips[ TILE_RED ].y = 0;
            gTileClips[ TILE_RED ].w = TILE_WIDTH;
            gTileClips[ TILE_RED ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_GREEN ].x = 0;
            gTileClips[ TILE_GREEN ].y = 80;
            gTileClips[ TILE_GREEN ].w = TILE_WIDTH;
            gTileClips[ TILE_GREEN ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BLUE ].x = 0;
            gTileClips[ TILE_BLUE ].y = 160;
            gTileClips[ TILE_BLUE ].w = TILE_WIDTH;
            gTileClips[ TILE_BLUE ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_TOPLEFT ].x = 80;
            gTileClips[ TILE_TOPLEFT ].y = 0;
            gTileClips[ TILE_TOPLEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_TOPLEFT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_LEFT ].x = 80;
            gTileClips[ TILE_LEFT ].y = 80;
            gTileClips[ TILE_LEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_LEFT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BOTTOMLEFT ].x = 80;
            gTileClips[ TILE_BOTTOMLEFT ].y = 160;
            gTileClips[ TILE_BOTTOMLEFT ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOMLEFT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_TOP ].x = 160;
            gTileClips[ TILE_TOP ].y = 0;
            gTileClips[ TILE_TOP ].w = TILE_WIDTH;
            gTileClips[ TILE_TOP ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_CENTER ].x = 160;
            gTileClips[ TILE_CENTER ].y = 80;
            gTileClips[ TILE_CENTER ].w = TILE_WIDTH;
            gTileClips[ TILE_CENTER ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BOTTOM ].x = 160;
            gTileClips[ TILE_BOTTOM ].y = 160;
            gTileClips[ TILE_BOTTOM ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOM ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_TOPRIGHT ].x = 240;
            gTileClips[ TILE_TOPRIGHT ].y = 0;
            gTileClips[ TILE_TOPRIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_TOPRIGHT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_RIGHT ].x = 240;
            gTileClips[ TILE_RIGHT ].y = 80;
            gTileClips[ TILE_RIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_RIGHT ].h = TILE_HEIGHT;
            
            gTileClips[ TILE_BOTTOMRIGHT ].x = 240;
            gTileClips[ TILE_BOTTOMRIGHT ].y = 160;
            gTileClips[ TILE_BOTTOMRIGHT ].w = TILE_WIDTH;
            gTileClips[ TILE_BOTTOMRIGHT ].h = TILE_HEIGHT;
        }
    }
    
    //Close the file
    map.close();
    
    //If the map was loaded
    return tilesLoaded;
}


////Circle/Circle collision detector
//bool checkCollision( Circle& a, Circle& b )
//{
//    //Calculate the total radius squared
//    int totalRadiusSquared = a.r + b.r;
//    totalRadiusSquared = totalRadiusSquared * totalRadiusSquared;
//    
//    //If the distance between the centers of the circle are less than the sum of their radii
//    if( distanceSquared( a.x, a.y, b.x, b.y ) < ( totalRadiusSquared ) )
//    {
//        //The circles have collided
//        return true;
//    }
//    
//    //if not
//    return false;
//}
//
////Circle/box collision detector
//bool checkCollision( Circle& a, SDL_Rect& b )
//{
//    //Closest point on collision box
//    int cx, cy;
//    
//    //Find closest x offset
//    if( a.x < b.x )
//    {
//        cx = b.x;
//    }
//    else if( a.x > b.x + b.w )
//    {
//        cx = b.x + b.w;
//    }
//    else{
//        cx = a.x;
//    }
//    //Find closest y offset
//    if( a.y < b.y )
//    {
//        cy = b.y;
//    }
//    else if( a.y > b.y + b.h )
//    {
//        cy = b.y + b.h;
//    }
//    else
//    {
//        cy = a.y;
//    }
//    
//    //If the closest point is inside the circle
//    if( distanceSquared( a.x, a.y, cx, cy ) < a.r * a.r )
//    {
//        //This box and circle have collided
//        return true;
//    }
//    
//    //If the shapes have no collided
//    return false;
//    
//}

double distanceSquared( int x1, int y1, int x2, int y2 )
{
    int deltaX = x2 - x1;
    int deltaY = y2 - y1;
    return deltaX*deltaX + deltaY*deltaY;
}

