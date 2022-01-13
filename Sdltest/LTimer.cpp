#include "LTimer.h"

LTimer::LTimer()
{
    _isPaused = false;
    _isStarted = false;
    _startTicks = 0;
    _pausedTicks = 0;
}

void LTimer::start()
{
    //Start the timer
    _isStarted = true;

    //Unpause the timer
    _isPaused = false;

    //Get current clock time
    _startTicks = SDL_GetTicks();
    _pausedTicks = 0;
}

void LTimer::stop()
{
    //Stop and unpause the timer
    _isStarted = false;
    _isPaused = false;

    //Clear ticks
    _startTicks = 0;
    _pausedTicks = 0;
}

void LTimer::pause()
{
    //If the timer is running and not paused
    if (_isStarted && !_isPaused) {
        //Pause the timer
        _isPaused = true;

        //Calculate paused ticks
        _pausedTicks = SDL_GetTicks() - _startTicks;
        _startTicks = 0;
    }
}

void LTimer::unpause()
{
    //If the timer is running and paused
    if (_isStarted && _isPaused) {
        //Unpause the timer
        _isPaused = false;

        //Reset the starting ticks
        _startTicks = SDL_GetTicks() - _pausedTicks;

        //Reset the paused ticks
        _pausedTicks = 0;
    }
}

Uint32 LTimer::getTicks()
{
    //The actual timer time
    Uint32 time = 0;

    //If the timer is running
    if (_isStarted) {
        //If it's paused
        if (_isPaused) {
            //Return the number of ticks when the timer was paused
            time = _pausedTicks;
        }
        else {
            //Return the current time minus the start time
            time = SDL_GetTicks() - _startTicks;
        }
    }

    return time;
}

bool LTimer::isStarted()
{
    return _isStarted;
}

bool LTimer::isPaused()
{
    return _isPaused && _isStarted;
}
