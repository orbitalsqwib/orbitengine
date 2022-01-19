// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Input Extension Class Specification
// ===========================================================================

#ifndef _ORBIT_WINDOW_INPUTEXTENSION_H
#define _ORBIT_WINDOW_INPUTEXTENSION_H

// import necessary headers
#include "windowExtension.h"
#include "../../common/priority.h"
#include "../../input/keyboardState.h"
#include "../../input/mouseState.h"
#include "../../messaging/pubsub.h"


// main definition

// provides keyboard support for the application by intercepting window input
// messages and updating a specified keyboard state container.
class InputExtension : public WindowExtension
{
private:

	// state containers

	// specifies a non-owning pointer to a keyboard state container, which
	// will be notified to update its state in response to the relevant inputs
	KeyboardState* keyboardState;

	// specifies a non-owning pointer to a mouse state container, which will
	// be notified to update its state in response to the relevant inputs
	MouseState* mouseState;

	
	// handlers

	// high-definition mouse handler
	RAWINPUTDEVICE rawInputDevices[1];


	// abstract initializer - will be called only when window extension has
	// been bound to a window. hwndPtr and commandBroker are only guaranteed
	// to exist when this method is invoked.
	virtual void initialize();


	// private methods

	// invokes the necessary methods to setup mouse input
	void initializeMouseHandler();

	// handles keyboard input messages
	void handleKeyboardInput(
		const UINT&		msg,
		const WPARAM&	wParam,
		const LPARAM&	lParam,
		Flow<LRESULT>&	flow
	);

	// handles mouse input messages
	void handleMouseInput(
		const UINT&		msg,
		const WPARAM&	wParam,
		const LPARAM&	lParam,
		Flow<LRESULT>&	flow
	);

public:

	// constructor
	InputExtension(
		KeyboardState*	_keyboardState	= nullptr,
		MouseState*		_mouseState		= nullptr
	);

	// destructor
	~InputExtension();


	// implement pure virtuals

	// code to be run as an extension within base wndproc
	virtual void wndProc(
		UINT			msg,
		WPARAM			wParam,
		LPARAM			lParam,
		Flow<LRESULT>&	flow
	);

};

#endif // !_ORBIT_WINDOW_INPUTEXTENSION_H