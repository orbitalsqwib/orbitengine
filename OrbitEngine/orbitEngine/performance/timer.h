// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Performance Timer Class Specification
// ===========================================================================

#ifndef _ORBIT_PERFORMANCE_TIMER_H
#define _ORBIT_PERFORMANCE_TIMER_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../error.h"

// include mmsystem header and accompanying winmm lib
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")


// main definition

// performance timer utility object - calculates performance metrics such as
// frame time and frames per second, while regulating frame rate.
class PerformanceTimer
{
private:

	// timer states

	// time taken for the last processing frame (seconds/frame)
	float frameTime;

	// time delay required to match target frame rate (seconds/frame)
	DWORD delayTime;

	// frames completed per second
	float fps;


	// configurable states

	// specifies the target frame rate for the timer. if set to 0, the timer
	// will not attempt to match a target frame rate.
	float targetFrameRate;

	// specifies the minimum frame rate for the timer. if set to 0, the timer
	// will not attempt to limit the frametime value used in the framerate
	// calculations.
	float minimumFrameRate;


	// working states

	// records the minimum allowed frame time to reach the target frame rate
	float minimumFrameTime;

	// records the maximum allowed frame time to reach the minimum frame rate
	float maximumFrameTime;

	// specifies when the timer last started (in ticks)
	LARGE_INTEGER	timeStart;

	// specifies when the timer last stopped (in ticks)
	LARGE_INTEGER	timeEnd;

	// specifies the current timer frequency (ticks/sec) 
	LARGE_INTEGER	frequency;

public:

	// constructor
	PerformanceTimer(
		const float&	_targetFrameRate	= 240,
		const float&	_minimumFrameRate	= 1
	);


	// methods

	// updates and recalculates timer states. if a target frame rate is
	// specified, this timer will intentionally add delays to reach the target
	// frame rate. returns the frametime for the last frame - if this is < 0,
	// the invoker should skip to the next frame.
	float runTimer();


	// getters

	// returns the current frames per second as a float
	float getFPS() const { return fps; }
};

#endif // !_ORBIT_PERFORMANCE_TIMER_H