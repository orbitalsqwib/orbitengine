// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Context Class Specification
// ===========================================================================

#ifndef _ORBIT_WINDOW_CONTEXT_H
#define _ORBIT_WINDOW_CONTEXT_H

// import necessary headers
#include "../!config.h"


// main definition

// provides a shared context layer between all window instances created from
// base window. enables features such as tracking the number of windows and
// static type-checks for crtp patterns.
class WindowContext {
private:

	// allow instantiation by base window
	template <class ChildWindow>
	friend class Window;

	// private constructor - prevent other classes from creating instances
	WindowContext() {}


	// fields

	// tracks the global number of window instances across the application
	static int windowCounter;

	// specifies if the window instance counter is enabled
	static bool windowCounterEnabled;

protected:

	// getters

	// return the number of window instances across the application
	int getWindowCount() const
	{
		return windowCounter;
	}


	// setters

	// enables or disables the global window counter
	void toggleWindowCounter(bool e) 
	{ 
		windowCounterEnabled = e;
	}

	// increment the number of window instances across the application
	void incrementWindows()
	{ 
		if(windowCounterEnabled) windowCounter++;
	}

	// decrement the number of window instances across the application
	void decrementWindows()
	{
		// quit early if window instance counter is inactive
		if (!windowCounterEnabled) return;

		// decrease nInstances by one
		windowCounter--;

		// if there are no instances left, handle quit according to settings
		if (windowCounter < 1 && SETTINGS_NS::QUIT_ON_ZERO_WINDOWS)
			PostQuitMessage(0);
	}
};

#endif // !_ORBIT_WINDOW_CORECONTEXT_H