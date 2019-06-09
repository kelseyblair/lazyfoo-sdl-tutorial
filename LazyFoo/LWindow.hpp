//
//  LWindow.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-22.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef LWindow_hpp
#define LWindow_hpp

#include <SDL2/SDL.h>

class LWindow
{
public:
    //Initialize internals
    LWindow();
    
    //Create window
    bool init();
    
    //Handles window events
    void handleEvent( SDL_Event& e );
    
    //Focuses on window
    void focus();
    
    //Shows window contents
    void render();
    
    //Deallocate internals
    void free();
    
    //Window dimensions
    int getWidth();
    int getHeight();
    
    //Window focii
    bool hasMouseFocus();
    bool hadKeyboardFocus();
    bool isMinimized();
    bool isShown();
    
private:
    //Window data
    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    int mWindowID;
    int mWindowDisplayID;
    
    //Window dimensions
    int mWidth;
    int mHeight;
    
    //Window focus
    bool mMouseFocus;
    bool mKeyboardFocus;
    bool mFullScreen;
    bool mMinimized;
    bool mShown;
    
};

#endif /* LWindow_hpp */
