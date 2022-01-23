// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Input Extension Class Implementation
// ===========================================================================

// import specification
#include "inputExtension.h"


// ===========================================================================
// constructor
// ===========================================================================
InputExtension::InputExtension(
	KeyboardState*	_keyboardState,
	MouseState*		_mouseState
):
	// members
	keyboardState	(_keyboardState),
	mouseState		(_mouseState),
	rawInputDevices	()
{}

// ===========================================================================
// destructor
// ===========================================================================
InputExtension::~InputExtension()
{
	// if mouse state was registered, and mouse is currently captured
	if (mouseState && mouseState->getCaptureState())
	{
		// release mouse capture
		ReleaseCapture();
	}
}

// ===========================================================================
// initializer - will be called only when window extension has been bound
// to a window. hwndPtr and commandBroker are only guaranteed to exist 
// when this method is invoked.
// ===========================================================================
void InputExtension::initialize()
{
	// guard against potential exceptions
	try
	{
		// initialize mouse handler
		initializeMouseHandler();
	}
	catch (...)
	{
		// catch any initialization errors
		throw(Error("Error! Failed to initialize input extension!"));
	}
}


// private methods

// ===========================================================================
// invokes the necessary methods to setup mouse input
// ===========================================================================
void InputExtension::initializeMouseHandler()
{
	// only initialize mouse handler if mouse state container was specified
	if (!mouseState) return;

	// initialize high-definition mouse device
	rawInputDevices[0].usUsagePage	= HID_USAGE_PAGE_GENERIC;
	rawInputDevices[0].usUsage		= HID_USAGE_GENERIC_MOUSE;
	rawInputDevices[0].dwFlags		= RIDEV_INPUTSINK;
	rawInputDevices[0].hwndTarget	= *hwndPtr;

	// register high-definition mouse device
	RegisterRawInputDevices(
		rawInputDevices,
		1,
		sizeof(rawInputDevices[0])
	);

	// capture mouse if enabled
	if (mouseState->getCaptureState()) SetCapture(*hwndPtr);
}

// ===========================================================================
// handles keyboard input messages
// ===========================================================================
void InputExtension::handleKeyboardInput(
	const UINT&		msg,
	const WPARAM&	wParam,
	const LPARAM&	lParam,
	Flow<LRESULT>&	flow
) {
	// non-state dependant inter-system command hotkeys (non-intercepting)
	if (msg == WM_KEYDOWN || msg == WM_SYSKEYDOWN)
	{
		switch (static_cast<UCHAR>(wParam))
		{
		// F11 - toggle borderless fullscreen
		case VK_F11:
			if (broker) broker->pushImmediately(
				DisplayCommands::TOGGLEBORDERLESSFULLSCREEN
			);
			break;

		case VK_F4:
			// ALT F4 - kills program immediately
			if ((HIWORD(lParam) & KF_ALTDOWN) == KF_ALTDOWN)
			{
				// send quit message
				PostQuitMessage(0);
			}
			break;
		}
	}

	// ensure keyboard state is bound and flow has not resolved
	if (!keyboardState || !flow.stillRunning()) return;

	// handle keyboard input messages 
	switch (msg)
	{
	// handle key down
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
	{
		keyboardState->notifyKeyDown(static_cast<UCHAR>(wParam));
		return flow.resolve(0);
	}

	// handle key up
	case WM_KEYUP:
	case WM_SYSKEYUP:
	{
		keyboardState->notifyKeyUp(static_cast<UCHAR>(wParam));
		return flow.resolve(0);
	}

	// handle character entered
	case WM_CHAR:
	{
		keyboardState->notifyTextIn(static_cast<UCHAR>(wParam));
		return flow.resolve(0);
	}
	}
}

// ===========================================================================
// handles mouse input messages
// ===========================================================================
void InputExtension::handleMouseInput(
	const UINT&		msg,
	const WPARAM&	wParam,
	const LPARAM&	lParam,
	Flow<LRESULT>&	flow
) {
	// ensure mouse state is bound and flow has not resolved
	if (!mouseState || !flow.stillRunning()) return;

	// handle mouse input messages 
	switch (msg)
	{
	// handle mouse movement
	case WM_MOUSEMOVE:
	{
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle raw mouse data input
	case WM_INPUT:
	{
		mouseState->notifyRawChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse left button down, update mouse position
	case WM_LBUTTONDOWN:
	{
		mouseState->notifyLBtnChanged(true);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse left button up, update mouse position
	case WM_LBUTTONUP:
	{
		mouseState->notifyLBtnChanged(false);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse middle button down, update mouse position
	case WM_MBUTTONDOWN:
	{
		mouseState->notifyMBtnChanged(true);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse middle button up, update mouse position
	case WM_MBUTTONUP:
	{
		mouseState->notifyMBtnChanged(false);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse right button down, update mouse position
	case WM_RBUTTONDOWN:
	{
		mouseState->notifyRBtnChanged(true);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse right button up, update mouse position
	case WM_RBUTTONUP:
	{
		mouseState->notifyRBtnChanged(false);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}

	// handle mouse x button down/up, update mouse position
	case WM_XBUTTONDOWN:
	case WM_XBUTTONUP:
	{
		mouseState->notifyXBtnChanged(wParam);
		mouseState->notifyPosChanged(lParam);
		return flow.resolve(0);
	}
	}
}


// implement pure virtuals

// ===========================================================================
// code to be run as an extension within base wndproc
// ===========================================================================
void InputExtension::wndProc(
	UINT			msg,
	WPARAM			wParam,
	LPARAM			lParam,
	Flow<LRESULT>&	flow
) {
	// handle input messages
	handleKeyboardInput(msg, wParam, lParam, flow);
	handleMouseInput(msg, wParam, lParam, flow);
}