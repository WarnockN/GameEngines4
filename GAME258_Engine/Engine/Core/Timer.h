#ifndef TIMER_H
#define TIMER_H

#include <SDL.h>

/*SHAKED SAYS: this is a way to remove "magic numbers"; things that other coders may get confused if they dont understand your code. 
we use this over define because we dont want the pre-processor to deal with this macro creation. 

The only time we should use the #define is when we have a #if statement.

this essentially is a constant float expression. its purpose is to convert milliseconds to seconds as seen in the name. 
*/
constexpr float MILLI_TO_SEC = 1000.0f;

class Timer {
public:
	/*singleton again. removes ability to copy this timer.*/
	Timer(const Timer&) = delete;
	Timer(Timer&&) = delete;
	Timer& operator=(const Timer&) = delete;
	Timer& operator=(const Timer&&) = delete;
	
	Timer();
	~Timer();

	void Start();
	void UpdateFrameTicks();
	float GetDeltaTime() const;
	unsigned int GetSleepTime(const unsigned int fps_) const;
	
	//gets the current ticks in milliseconds
	inline float GetCurrTicksMilli() const { return static_cast<float>(currTicks); }

	//gets the current ticks in seconds, added both for variance, and ease of use.
	inline float GetCurrTickSec() const { return currTicks / MILLI_TO_SEC; }

private:
	unsigned int prevTicks;
	unsigned int currTicks;
};
#endif

