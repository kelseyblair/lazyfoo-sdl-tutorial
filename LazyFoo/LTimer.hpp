//
//  LTimer.hpp
//  SDL_Tutorial
//
//  Created by Kelsey Blair on 2016-08-20.
//  Copyright © 2016 Kelsey Blair. All rights reserved.
//

#ifndef LTimer_hpp
#define LTimer_hpp

#include <SDL2/SDL.h>

class LTimer
{
public:
    //Initialized variables
    LTimer();
    
    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();
    
    //Gets the timer's time
    Uint32 getTicks();
    
    //Checks the status of the timer
    bool isStarted();
    bool isPaused();
    
private:
    //The clock time when the timer started
    Uint32 mStartTicks;
    
    //The ticks stored when the timer was paused
    Uint32 mPausedTicks;
    
    //The time status
    bool mPaused;
    bool mStarted;
};

#endif /* LTimer_hpp */
