// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Display Extension Class Specification
// ===========================================================================

#ifndef _ORBIT_WINDOW_DISPLAYEXTENSION_H
#define _ORBIT_WINDOW_DISPLAYEXTENSION_H

// import necessary headers
#include "windowExtension.h"
#include "../../!config.h"
#include "../../common/priority.h"
#include "../../common/windowStyle.h"
#include "../../messaging/pubsub.h"
#include <limits.h>
#include <windowsx.h>

// include dwmapi and its linker dependency for window composition
#pragma comment (lib, "dwmapi.lib")
#include <dwmapi.h>

// default values
namespace {

	// constructor

	const WindowStyle		D_WINDOWSTYLE
		= WindowStyle::UNSET;

	const bool		D_BORDERLESSFULLSCREEN
		= FALSE;

	const bool		D_RESIZEENABLED
		= FALSE;

	const bool		D_DRAGENABLED
		= FALSE;

	const bool		D_SHADOWENABLED
		= TRUE;
}


// main definition

// extends the display capabilities for a window.
//   - adds support for borderless windows
//   - enables finer control over window controls (resize, drag)
//   - enables finer control over display elements (shadows)
class DisplayExtension : 
	public WindowExtension,
	public ISubscriber<WindowDisplayCommands>
{
private:

	// members

	// records the current availability of the desktop window manager
	// composition API
	BOOL dwmCompositionAvailable;


	// behavioural states

	// specifies the current style (borderless/bordered) of the window
	WindowStyle windowStyle;

	// specifies if the window is currently in borderless fullscreen
	bool borderlessFullscreen;

	// specifies if the window should be resizable
	bool resizeEnabled;

	// specifies if the window should be draggable
	bool dragEnabled;

	// specifies if the window should display edge shadows
	bool shadowEnabled;


	// working states

	MONITORINFO monitorInfo;

	WINDOWPLACEMENT	wndPlacement;


	// initializer - will be called only when window extension has been bound
	// to a window. hwndPtr and commandBroker are only guaranteed to exist 
	// when this method is invoked.
	void initialize();


	// private methods

	// obtains the monitor information for the managed window and writes it
	// into the specified monitor info struct
	bool getMonitorInfo(const LPMONITORINFO& lpMonitorInfo);

	// checks if the managed window is currently maximised
	bool isMaximised();

	// calculates custom cursor hit-tests for managed windows
	LRESULT cursorHitTest(const POINT& cursorPos);

	// toggles the native soft edge shadows for the managed window
	void toggleShadow(const bool& enabled);

	// updates the current style of the managed window, toggling the
	// visibility of the managed window in the process
	void setStyle(
		WindowStyle		windowStyle,
		const bool&		showWindow		= true
	);

	// toggles between borderless fullscreen and bordered windowed mode
	void toggleBorderlessFullscreen(bool enabled);

public:

	// constructor
	DisplayExtension();


	// implement pure virtuals

	// should handle incoming messages and make changes to the object's state
	// or behaviour as necessary. may provide a pointer to the message broker
	// that invoked this event, which should be null-checked prior to use.
	virtual void handleMessage(
		WindowDisplayCommands	command,
		MessageBroker*			broker
	);

	// code to be run as an extension within base wndproc
	virtual void wndProc(
		UINT			msg,
		WPARAM			wParam,
		LPARAM			lParam,
		Flow<LRESULT>&	flow
	);

};

#endif // !_ORBIT_WINDOW_DISPLAYEXTENSION_H