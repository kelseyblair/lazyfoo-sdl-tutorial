//
//  program.h
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-19.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef program_h
#define program_h


#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <fstream>

#include "LTexture.hpp"
#include "LButton.hpp"
#include "LButtonSprite.h"
#include "LTimer.hpp"
#include "Dot.hpp"
#include "LWindow.hpp"
#include "Tile.hpp"
#include "TileSprites.h"

// GLOBAL VARIABLE DECLARATIONS
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_FPS;
extern const int SCREEN_TICKS_PER_FRAME;
extern const int TOTAL_WINDOWS;

extern const int LEVEL_WIDTH;
extern const int LEVEL_HEIGHT;

extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
extern const int TOTAL_BUTTONS;

extern const int TOTAL_DATA;

extern const int TOTAL_PARTICLES;

extern const int TILE_WIDTH;
extern const int TILE_HEIGHT;
extern const int TOTAL_TILES;

extern SDL_Renderer* gRenderer;
extern SDL_Window* gWindow;
//extern LWindow gWindow;
extern int gTotalDisplays;
extern SDL_Rect* gDisplayBounds;

extern LTexture gSceneTexture;

extern SDL_Rect gSpriteClips[ BUTTON_SPRITE_TOTAL ];

extern TTF_Font* gFont;

extern LTexture gPromptTextTexture;

extern LTexture gButtonSpriteSheetTexture;

extern LTexture gBackgroundTexture;

extern LTexture gDotTexture;

extern LTexture gRedTexture;
extern LTexture gGreenTexture;
extern LTexture gBlueTexture;
extern LTexture gShimmerTexture;

extern LTexture gTileTexture;
extern SDL_Rect gTileClips[];

// FUNCTION DEFINITIONS
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia( Tile* tiles[] );

//Frees media and shuts down SDL
void close( Tile* tiles[] );


////Circle/Circle and Circle/Box collision detector
//bool checkCollision( Circle& a, Circle& b );
//bool checkCollision( Circle& a, SDL_Rect& b );
bool checkCollision( SDL_Rect a, SDL_Rect b );

//checks collisions box against a set of tiles
bool touchesWall( SDL_Rect box, Tile* tiles[] );

//Sets tiles from tile map
bool setTiles( Tile *tiles[] );

//Calculate distance square between two points
double distanceSquared( int x1, int y1, int x2, int y2 );


#endif /* program_h */
