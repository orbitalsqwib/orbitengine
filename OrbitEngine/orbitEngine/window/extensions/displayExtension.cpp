// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Display Extension Class Implementation
// ===========================================================================

// import specification
#include "displayExtension.h"


// ===========================================================================
// constructor
// ===========================================================================
DisplayExtension::DisplayExtension():

	// config states
	windowStyle				(D_WINDOWSTYLE),
	borderlessFullscreen	(D_BORDERLESSFULLSCREEN),
	resizeEnabled			(D_RESIZEENABLED),
	dragEnabled				(D_DRAGENABLED),
	shadowEnabled			(D_SHADOWENABLED),

	// working states
	monitorInfo		(),
	wndPlacement	()
{
	// check if dwm-based window composition is available
	DwmIsCompositionEnabled(&dwmCompositionAvailable);
}

// ===========================================================================
// initializer - will be called only when window extension has been bound
// to a window. hwndPtr and commandBroker are only guaranteed to exist 
// when this method is invoked.
// ===========================================================================
void DisplayExtension::initialize()
{
	// register self with command broker
	broker->addSubscriber(*this);
}


// private methods

// ===========================================================================
// obtains the monitor information for the managed window and writes it
// into the specified monitor info struct
// ===========================================================================
bool DisplayExtension::getMonitorInfo(
	const LPMONITORINFO&	_lpMonitorInfo
) {
	// initialise monitorinfo cbSize before processing
	_lpMonitorInfo->cbSize = sizeof(*_lpMonitorInfo);

	// attempt to get current monitor for window instance
	HMONITOR hMonitor =
		MonitorFromWindow(*hwndPtr, MONITOR_DEFAULTTONULL);

	// ensure monitor handle is properly retrieved
	if (!hMonitor) return false;

	// load monitor info into specified struct and return result status
	return GetMonitorInfo(hMonitor, _lpMonitorInfo) ? true : false;
}

// ===========================================================================
// checks if the managed window is currently maximised
// ===========================================================================
bool DisplayExtension::isMaximised()
{
	// attempt to retrieve current show state for the bound window
	if (!GetWindowPlacement(*hwndPtr, &wndPlacement)) return FALSE;

	// return show state for bound window
	return wndPlacement.showCmd == SW_MAXIMIZE;
}

// ===========================================================================
// calculates custom cursor hit-tests for borderless windows
// ===========================================================================
LRESULT DisplayExtension::cursorHitTest(
	const POINT&	cursorPos
) {
	// get resizing frame metrics for window
	// SM_CXFRAME is the width of the horizontal sizing border
	// SM_CYFRAME is the height of the vertical sizing border
	// SM_CXPADDEDBORDER is the amount of border padding for captioned windows
	const int frameW 
		= GetSystemMetrics(SM_CXFRAME) 
		+ GetSystemMetrics(SM_CXPADDEDBORDER);
	const int frameH 
		= GetSystemMetrics(SM_CYFRAME) 
		+ GetSystemMetrics(SM_CXPADDEDBORDER);

	// retrieve the bounding rectangle of our bound window instance,
	// fail gracefullly if no window bounds are found
	RECT bounds;
	if (!GetWindowRect(*hwndPtr, &bounds)) return HTNOWHERE;

	// if drag is enabled, cursor is interpreted as clicking (and dragging)
	// the caption area of the window. else, it is interpreted as having
	// clicked within the client area
	const BOOL dragRegion = dragEnabled ? HTCAPTION : HTCLIENT;

	// define a mask for the top, bottom, left and right frame regions
	// if the cursor is not on the frame, it must be within the client area
	enum region_mask {
		left		= 0b0001,
		right		= 0b0010,
		top			= 0b0100,
		bottom		= 0b1000,
		client		= 0b0000,
	};
	
	// now calculate whether the cursor is within each of the regions,
	// perform a logical AND on the result and the appropriate region
	// mask, then OR all the regions together. this allows us to
	// represent the cursor region with just a single INT8 variable.
	const INT8 hitRegion =
		left	* (cursorPos.x <  (bounds.left	+ frameW)) |
		right	* (cursorPos.x >= (bounds.right	- frameW)) |
		top		* (cursorPos.y <  (bounds.top	+ frameH)) |
		bottom	* (cursorPos.y >= (bounds.bottom - frameH));

	// finally, return the corresponding hit test region
	// for the region we calculated. note that if resizing
	// is disabled, we default it to a drag instead.

	// return appropriate hitRegion according to region calculations
	switch (hitRegion) {
	case left:
		return resizeEnabled ? HTLEFT			: dragRegion;
	case right:
		return resizeEnabled ? HTRIGHT			: dragRegion;
	case top:
		return resizeEnabled ? HTTOP			: dragRegion;
	case bottom:
		return resizeEnabled ? HTBOTTOM			: dragRegion;
	case top|left:
		return resizeEnabled ? HTTOPLEFT		: dragRegion;
	case top|right:
		return resizeEnabled ? HTTOPRIGHT		: dragRegion;
	case bottom|left:
		return resizeEnabled ? HTBOTTOMLEFT		: dragRegion;
	case bottom|right:
		return resizeEnabled ? HTBOTTOMRIGHT	: dragRegion;
	case client:
		return dragRegion;

	// this is what happens if a cursor is somehow simultaneously
	// clicking the top and bottom of the window or something like that
	default:
		return HTNOWHERE;
	}
}

// ===========================================================================
// toggles the native soft edge shadows for the managed window
// ===========================================================================
void DisplayExtension::toggleShadow(
	const bool&	enabled
) {
	// ensure dwm composition is available and shadows are enabled
	if (!dwmCompositionAvailable && shadowEnabled) return;

	// define frame margins that have visual styles applied
	static const MARGINS shadowsForState[2]{
		{0, 0, 0, 0}, // disabled
		{1, 1, 1, 1}  // enabled
	};

	// extends the frame into the client area, which sets the shadows
	DwmExtendFrameIntoClientArea(*hwndPtr, &shadowsForState[enabled]);
}

// ===========================================================================
// updates the current style of the managed window, toggling the
// visibility of the managed window in the process
// ===========================================================================
void DisplayExtension::setStyle(
	WindowStyle		_windowStyle,
	const bool&		showWindow
) {
	// use fallback non-window-composition compatible style
	if (!dwmCompositionAvailable && _windowStyle == WindowStyle::BORDERLESS)
		_windowStyle = WindowStyle::BD_FALLBACK;

	// update window styles
	windowStyle = _windowStyle;
	SetWindowLong(*hwndPtr, GWL_STYLE, static_cast<LONG>(windowStyle));

	// update window shadows for style
	toggleShadow(windowStyle != WindowStyle::BORDERED);

	// redraw window frames
	SetWindowPos(
		*hwndPtr, 
		NULL, 
		0, 0, 0, 0, 
		SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE
	);

	// update window presentation style and repaint
	ShowWindow(*hwndPtr, showWindow ? SW_SHOW : SW_HIDE);
	UpdateWindow(*hwndPtr);
}

// ===========================================================================
// toggles between borderless fullscreen and bordered windowed mode
// ===========================================================================
void DisplayExtension::toggleBorderlessFullscreen(bool enabled)
{
	// update flag
	borderlessFullscreen = enabled;

	// update window to reflect flag
	if (borderlessFullscreen)
	{
		setStyle(WindowStyle::BORDERLESS);
		ShowWindow(*hwndPtr, SW_MAXIMIZE);
		UpdateWindow(*hwndPtr);
	}
	else
	{
		setStyle(WindowStyle::BORDERED);
		SetWindowPos(
			*hwndPtr,
			NULL,
			SETTINGS_NS::WND_INIT_X,
			SETTINGS_NS::WND_INIT_Y,
			SETTINGS_NS::WND_INIT_WIDTH,
			SETTINGS_NS::WND_INIT_HEIGHT,
			NULL
		);
		UpdateWindow(*hwndPtr);
	}
}

// ===========================================================================
// translates window commands to modifications of extension behaviour or
// state. the function should return true to halt subsequent processing
// for the same window command.
// ===========================================================================
void DisplayExtension::handleMessage(
	WindowDisplayCommands	command,
	MessageBroker*			
) {
	// switch by command id
	switch (command)
	{
	// SETSTYLE
	case WindowDisplayCommands::SETSTYLE_BORDERED:
		setStyle(WindowStyle::BORDERED);	break;
	case WindowDisplayCommands::SETSTYLE_BORDERLESS:
		setStyle(WindowStyle::BORDERLESS);	break;
	case WindowDisplayCommands::SETSTYLE_UNSET:
		setStyle(WindowStyle::UNSET);		break;

	// SETRESIZE
	case WindowDisplayCommands::SETRESIZE_OFF:
		resizeEnabled = false;	break;
	case WindowDisplayCommands::SETRESIZE_ON:
		resizeEnabled = true;	break;

	// SETDRAGGING
	case WindowDisplayCommands::SETDRAGGING_OFF:
		dragEnabled = false;	break;
	case WindowDisplayCommands::SETDRAGGING_ON:
		dragEnabled = true;		break;

	// SETDRAGGING
	case WindowDisplayCommands::SETSHADOWS_OFF:
		shadowEnabled = false;	break;
	case WindowDisplayCommands::SETSHADOWS_ON:
		shadowEnabled = true;	break;

	// BORDEREDWINDOWED
	case WindowDisplayCommands::BORDEREDWINDOWED:
		toggleBorderlessFullscreen(false);
		break;

	// BORDERLESSFULLSCREEN
	case WindowDisplayCommands::BORDERLESSFULLSCREEN:
		toggleBorderlessFullscreen(true);
		break;

	// TOGGLEBORDERLESSFULLSCREEN
	case WindowDisplayCommands::TOGGLEBORDERLESSFULLSCREEN:
		toggleBorderlessFullscreen(!borderlessFullscreen);
		break;
	}
}

// ===========================================================================
// code to be run as an extension within base wndproc
// ===========================================================================
void DisplayExtension::wndProc(
	UINT			msg,
	WPARAM			wParam,
	LPARAM			lParam,
	Flow<LRESULT>&	flow
) {
	// do not handle any messages until style is set
	if (windowStyle == WindowStyle::UNSET) return;

	// handle extension specific messages
	switch (msg)
	{
	// recalculate size and position of window client area when fullscreen
	case WM_NCCALCSIZE:
	{
		// if wParam is true, we can do our own processing,
		// else we should just return false
		if (wParam == TRUE && windowStyle == WindowStyle::BORDERLESS)
		{
			// better fullscreen resizing
			if (isMaximised()) {

				// initialise monitor info struct
				ZeroMemory(&monitorInfo, sizeof(&monitorInfo));

				// attempt to load monitor info into struct
				if (getMonitorInfo(&monitorInfo)) {

					// get resizing params from lParam-pointed struct
					NCCALCSIZE_PARAMS* params = 
						reinterpret_cast<NCCALCSIZE_PARAMS*>(lParam);

					// propose the monitor's fullscreen workarea as the new
					// window area
					params->rgrc[0] = monitorInfo.rcWork;
				}
			}

			// setting the result to false here is actually what enables us
			// to make the window "borderless", as it causes the client area
			// to resize to the entire size of the window, thus removing all
			// window frame and caption items from the window.

			// always return false for borderless windows and skip all
			// remaining handlers, since this logic will be useless if
			// DefWindowProc() is called after this function!
			flow.resolve(FALSE);
		}
		break;
	}

	// perform own hit testing if window is borderless
	case WM_NCHITTEST:
	{
		if (windowStyle == WindowStyle::BORDERLESS)
		{
			// do manual hit testing, update pipeline as highest priority
			// then skip all remaining handlers
			flow.resolve(
				cursorHitTest(POINT{
					GET_X_LPARAM(lParam),
					GET_Y_LPARAM(lParam)
				})
			);
		}
		break;
	}

	case WM_NCACTIVATE:
	{
		if (!dwmCompositionAvailable)
		{
			// always return true when dwm composition is not
			// enabled, skip all remaining handlers
			flow.resolve(TRUE);
		}
		break;
	}
	}
}