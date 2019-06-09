//
//  main.cpp
//  SDL_Tutorial by Lazy Foo
//
//  Created by Kelsey Blair on 2015-09-12.
//  Copyright (c) 2015 Kelsey Blair. All rights reserved.
//

/*This source code copyrighted by Lazy Foo' Productions (2004-2015)
 and may not be redistributed without written permission.*/

//Using SDL and standard IO


#include "program.h"
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <cmath>
#include <sstream>
#include <fstream>


int main( int argc, char* args[] )
{
    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Initialize the window
        //        gWindow.init();
        
        //The level tiles
        Tile* tileSet[ TOTAL_TILES ];
        
        //Load media
        if( !loadMedia( tileSet ) )
        {
            printf( "Failed to load media!\n" );
        }
        else
        {
            //Main loop flag
            bool quit = false;
            
            //Event handler
            SDL_Event e;
            
            //The dot that will move around the screen
            Dot dot;
            
            //Camera
            SDL_Rect camera = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
            
            //While application is running
            while( !quit )
            {
                //Handle events on queue
                while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = true;
                    }
                    
                    //Handle input for the dot
                    dot.handleEvent( e );
                    
                    
                }
                //Move the dot
                dot.move( tileSet );
                dot.setCamera( camera );
                
                //Clear screen
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                
                //render level
                for( int i = 0; i < TOTAL_TILES; ++i )
                {
                    tileSet[ i ]->render( camera );
                }
                
                //Render dot
                dot.render( camera );
                
                SDL_RenderPresent( gRenderer );
            }
        }
        
        //Free resources and close SDL
        close( tileSet );
        
        return 0;
    }
}