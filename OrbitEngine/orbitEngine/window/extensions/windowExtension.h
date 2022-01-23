// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Extension Class Specification
// ===========================================================================

#ifndef _ORBIT_WINDOW_WINDOWEXTENSION_H
#define _ORBIT_WINDOW_WINDOWEXTENSION_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../../messaging/pubsub.h"
#include "../../utils/flow.h"

// forward class declarations
template <class ChildWindow> class Window;


// main definition

// specifies the behaviours that must be implemented for a window extension
class WindowExtension
{
private:

	// private setters

	// declare that only the base window class can call bind to window
	template <class ChildWindow>
	friend class Window;

	// binds the extension to the window
	template <class ChildWindow>
	void bindToWindow(Window<ChildWindow>* window)
	{
		hwndPtr			= window->getHwndPtr();
		broker			= window->getBroker();
		initialize();
	}

	// abstract initializer - will be called only when window extension has
	// been bound to a window. hwndPtr and commandBroker are only guaranteed
	// to exist when this method is invoked.
	virtual void initialize() = 0;

protected:

	// members

	// specifies a non-owning pointer to the handle of the managed window
	HWND* hwndPtr;

	// specifies the pointer to the shared command broker
	MessageBroker* broker;

public:

	// default constructor
	WindowExtension():

		// members
		hwndPtr	(nullptr),
		broker	(nullptr)
	{}

	// abstract virtual destructor
	virtual ~WindowExtension() {}


	// abstract methods

	// code to be run as an extension within base wndproc
	virtual void wndProc(
		UINT			msg,
		WPARAM			wParam,
		LPARAM			lParam,
		Flow<LRESULT>&	flow
	) = 0;
};

#endif // !_ORBIT_WINDOW_IWINDOWEXTENSION_H