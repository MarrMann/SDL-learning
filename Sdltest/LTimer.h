#include <SDL_stdinc.h>
#include <SDL_timer.h>

//The application time based timer
class LTimer
{
public:
	//Initializes variables
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
	Uint32 _startTicks;

	//The ticks stored when the timer was paused
	Uint32 _pausedTicks;

	//The timer status
	bool _isPaused;
	bool _isStarted;
};

