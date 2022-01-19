// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Performance Timer Class Implementation
// ===========================================================================

// import specification
#include "timer.h"


// ===========================================================================
// constructor
// ===========================================================================
PerformanceTimer::PerformanceTimer(
	const float&	_targetFrameRate,
	const float&	_minimumFrameRate
):
	// timer states
	frameTime	(0),
	delayTime	(0),
	fps			(0),

	// config. states
	targetFrameRate		(_targetFrameRate),
	minimumFrameRate	(_minimumFrameRate),

	// working states
	minimumFrameTime	(0),
	maximumFrameTime	(0),
	timeStart			(),
	timeEnd				(),
	frequency			()
{
	// calculate minimum frame time and maximum frame time
	minimumFrameTime = targetFrameRate > 0 ? 1.0f / targetFrameRate : 0;
	maximumFrameTime = minimumFrameRate > 0 ? 1.0f / minimumFrameRate : 0;

	// initialize high-resolution (<1 microsecond) timer
	if (!QueryPerformanceFrequency(&frequency))
	{
		// if setup failed, throw fatal exception
		throw(Error("Error initializing high-resolution timer!"));
	}

	// set start time to the current performance counter value
	QueryPerformanceCounter(&timeStart);
}


// methods

// ===========================================================================
// updates and recalculates timer states. if a target frame rate is
// specified, this timer will intentionally add delays to reach the target
// frame rate. returns the frametime for the last frame - if this is 0,
// the invoker should not process another frame.
// ===========================================================================
float PerformanceTimer::runTimer()
{
	// update end time to the current performance counter value
	QueryPerformanceCounter(&timeEnd);

	// calculate ticks elapsed since the end of the last frame
	frameTime = static_cast<float>(timeEnd.QuadPart - timeStart.QuadPart);

	// convert frame time from ticks to seconds
	frameTime /= static_cast<float>(frequency.QuadPart);

	// check if frametime is smaller than the minimum allotted frame time.
	if (minimumFrameTime > 0 && frameTime < minimumFrameTime)
	{
		// if so, calculate the additional delay required to hit the minimum
		// allotted frame time, then compensate for it by sleeping for that
		// duration.

		// calculate required delay
		delayTime = static_cast<DWORD>((minimumFrameTime - frameTime) * 1000);

		// request 1ms resolution for sleep timer
		timeBeginPeriod(1);

		// free processor for duration of delay
		Sleep(delayTime);

		// end 1ms resolution and resume normal processing
		timeEndPeriod(1);

		// skip to next timer cycle
		return 0.0f;
	}
	// else, if framerate over minimum allotted frame time, continue normally

	// calculate current fps (check prevents divide by zero error)
	if (frameTime > 0.0) fps = (fps * 0.99f) + (0.1f / frameTime);

	// cap maximum frametime if frame processing becomes exceedingly slow
	if (maximumFrameTime > 0 && frameTime > maximumFrameTime)
	{
		frameTime = maximumFrameTime;
	}

	// update start time to the previous end time for next timer cycle
	timeStart = timeEnd;

	// return frametime
	return frameTime;
}