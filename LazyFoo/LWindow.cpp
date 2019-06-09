//
//  LWindow.cpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-22.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#include "LWindow.hpp"
#include <sstream>

#include "program.h"

LWindow::LWindow()
{
    //Initialize non-existent window
    mWindow = NULL;
    mMouseFocus = false;
    mKeyboardFocus = false;
    mFullScreen = false;
    mMinimized = false;
    mShown = false;
    mWidth = 0;
    mHeight= 0;
    
    mWindowID = 0;
}

bool LWindow::init()
{
    //Create window
    mWindow = SDL_CreateWindow( "SDL_Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE );
    if( mWindow != NULL )
    {
        mMouseFocus = true;
        mKeyboardFocus = true;
        mWidth = SCREEN_WIDTH;
        mHeight = SCREEN_HEIGHT;
        
        
        //Create renderer for window
        mRenderer = SDL_CreateRenderer( mWindow, -1,  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
        if( mRenderer == NULL )
        {
            printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
            SDL_DestroyWindow( mWindow );
            mWindow = NULL;
        }
        else
        {
            //Initialize renderer color
            SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            
            //Grab window identifier
            mWindowID = SDL_GetWindowID( mWindow );
            mWindowDisplayID = SDL_GetWindowDisplayIndex( mWindow );
            
            mShown = true;
        }
    }
    else
    {
        printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
    }
    
    return mWindow != NULL && mRenderer != NULL;
}

void LWindow::handleEvent( SDL_Event& e )
{
    //Window event occurred
    if( e.type == SDL_WINDOWEVENT && e.window.windowID == mWindowID )
    {
        //Caption update flag
        bool updateCaption = false;
        
        switch ( e.window.event )
        {
                //Window moved
            case SDL_WINDOWEVENT_MOVED:
                mWindowDisplayID = SDL_GetWindowDisplayIndex( mWindow );
                updateCaption = true;
                break;
                
                //Window appeared
            case SDL_WINDOWEVENT_SHOWN:
                mShown = true;
                break;
                
                //Window disappeared
            case SDL_WINDOWEVENT_HIDDEN:
                mShown = false;
                break;
                
                //Get new dimensions and repaint
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                mWidth = e.window.data1;
                mHeight = e.window.data2;
                SDL_RenderPresent( mRenderer );
                break;
            
                //Repaint on exposure
            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent( mRenderer );
                break;
                
                //Mouse entered window
            case SDL_WINDOWEVENT_ENTER:
                mMouseFocus = true;
                updateCaption = true;
                break;
                
                //Mouse left window
            case SDL_WINDOWEVENT_LEAVE:
                mMouseFocus = false;
                updateCaption = true;
                break;
                
                //Window had keyboard focus
            case SDL_WINDOWEVENT_FOCUS_GAINED:
                mKeyboardFocus = true;
                updateCaption = true;
                break;
                
                //Window lost keyboard focus
            case SDL_WINDOWEVENT_FOCUS_LOST:
                mKeyboardFocus = false;
                updateCaption = true;
                break;
                
                //Window minimized
            case SDL_WINDOWEVENT_MINIMIZED:
                mMinimized = true;
                break;
                
                //Window maximixed
            case SDL_WINDOWEVENT_MAXIMIZED:
                mMinimized = false;
                break;
                
                //Window restored
            case SDL_WINDOWEVENT_RESTORED:
                mMinimized = false;
                break;
                
                //Hide on close
            case SDL_WINDOWEVENT_CLOSE:
                SDL_HideWindow( mWindow );
                break;
        }
        /******* MULTIPLE DISPLAY HANDLING***********
         else if( e.type == SDL_KEYDOWN )
         {
            //Display change flag
            bool switchDisplay = false;
         
            //Cycle through displays on up/down
            switch( e.key.keysym.sym )
            {
                case SDLK_UP:
                ++mWindowDisplayID;
                switchDisplay = true;
                break;
         
                case SDLK_DOWN:
                --mWindowDisplayID;
                switchDisplay = true;
                break;
            }
            //Display needs to be updated
            if( switchDisplay )
            {
                //Bound display index
            if( mWindowDisplayID < 0 )
            {
                mWindowDisplayID = gTotalDisplays - 1;
            }
            else if( mWindowDisplayID >= gTotalDisplays )
            {
                mWindowDisplayID = 0;
            }
         
            //Move window to center of next display
            SDL_SetWindowPosition( mWindow, gDisplayBounds[ mWindowDisplayID ].x + ( gDisplayBounds[ mWindowDisplayID ].w - mWidth ) / 2, gDisplayBounds[ mWindowDisplayID ].y + ( gDisplayBounds[ mWindowDisplayID ].h - mHeight ) / 2 );
            updateCaption = true;
         }
         *******************************************/
        
        //Update window caption with our new data
        if( updateCaption )
        {
            std::stringstream caption;
            caption << "SDL_Tutorial - ID: " << mWindowID << " Display " << mWindowDisplayID  << " MouseFocus: " << ( ( mMouseFocus ) ? "On ": "Off ") << "KeyboardFocus: " << ( ( mKeyboardFocus ) ? "On": "Off" );
            SDL_SetWindowTitle( mWindow, caption.str().c_str() );
        }
    }
    //Enter exit full screen on return key
    else if( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_RETURN )
    {
        if( mFullScreen )
        {
            SDL_SetWindowFullscreen( mWindow, SDL_FALSE );
            mFullScreen = false;
        }
        else
        {
            SDL_SetWindowFullscreen( mWindow, SDL_TRUE );
            mFullScreen = true;
            mMinimized = false;
        }
    }
}

void LWindow::focus()
{
    //Restore window if needed
    if( !mShown )
    {
        SDL_ShowWindow( mWindow );
    }
    //Move window forward
    SDL_RaiseWindow( mWindow );
}

void LWindow::render()
{
    if( !mMinimized )
    {
        //Clear screen
        SDL_SetRenderDrawColor( mRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( mRenderer );
        
        //Update screen
        SDL_RenderPresent( mRenderer );
    }
}

void LWindow::free()
{
    if( mWindow != NULL )
    {
        SDL_DestroyWindow( mWindow );
    }
    
    mMouseFocus = false;
    mKeyboardFocus = false;
    mWidth = 0;
    mHeight = 0;
}

int LWindow::getWidth()
{
    return mWidth;
}

int LWindow::getHeight()
{
    return  mHeight;
}

bool LWindow::hasMouseFocus()
{
    return mMouseFocus;
}

bool LWindow::hadKeyboardFocus()
{
    return mKeyboardFocus;
}

bool LWindow::isMinimized()
{
    return mMinimized;
}

bool LWindow::isShown()
{
    return mShown;
}