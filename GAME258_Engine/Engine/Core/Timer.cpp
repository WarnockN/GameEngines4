#include "Timer.h"

Timer::Timer() : prevTicks(0), currTicks(0) {}

Timer::~Timer() {}

/*set ticks to SDL_GetTicks -- the number of milliseconds since SDL inits.
  we are initiliazing this timer in widow with SDL_Init.

  always make sure tp update previous ticks before current ticks, this is relatively self explanatory
*/
void Timer::Start() {
	prevTicks = currTicks = SDL_GetTicks();
}

//updates both of our ticks. set previous to current, and then change current to SDL_GetTicks()
void Timer::UpdateFrameTicks() {
	prevTicks = currTicks;
	currTicks = SDL_GetTicks();
}

//get the time from previous frame to  current frame, in SECONDS.
float Timer::GetDeltaTime() const {
	return (currTicks - prevTicks) / MILLI_TO_SEC;
}

/*gets the time for sleep. gets the amount of time that the engine needs to sleep for to maintain the FPS value.
  takes in an fps int value, letting us set the fps value to whatever we choose. can also limit fps for consistency.

*/
unsigned int Timer::GetSleepTime(const unsigned int fps_) const { 
	unsigned int milliSecsPerFrame = MILLI_TO_SEC / fps_;
	if (milliSecsPerFrame == 0) return 0;

	unsigned int sleepTime = milliSecsPerFrame - (SDL_GetTicks() - currTicks);
	if (sleepTime > milliSecsPerFrame) return milliSecsPerFrame;

	return sleepTime;
}	