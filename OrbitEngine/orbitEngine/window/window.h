// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Window Abstract Base Class Specification
// ===========================================================================

#ifndef _ORBIT_WINDOW_WINDOW_H
#define _ORBIT_WINDOW_WINDOW_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "windowContext.h"
#include "extensions/windowExtension.h"
#include "../!config.h"
#include "../common/notifications/windowResized.h"
#include "../macros.h"
#include "../messaging/pubsub.h"
#include "../utils/flow.h"
#include "../utils/pointers.h"
#include <type_traits>

// default values
namespace {

	// constructor

	const LPCWSTR	D_LPSZMENUNAME
		= NULL;

	const UINT		D_STYLE
		= CS_HREDRAW | CS_VREDRAW;

	const HBRUSH	D_HBRUSH
		= static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));

	const HICON		D_HICON
		= NULL;

	const HICON		D_HICON_SM
		= NULL;

	const HCURSOR	D_HCURSOR
		= LoadCursor(NULL, IDC_ARROW);

	// bindWindow()

	const LPCWSTR	D_MUTEXNAME
		= NULL;

	const HWND		D_HWNDPARENT
		= NULL;

	const HMENU		D_HMENU
		= NULL;

	const DWORD		D_DWSTYLE
		= NULL;

	const DWORD		D_DWEXSTYLE
		= NULL;
}


// main definition

// abstract base window class for all window classes. provides basic window
// creation and management functionalities, which can be expanded upon using
// window extensions.
template <class ChildWindow>
class Window : public WindowContext
{
private:

	// internal typedefs

	// vector of unique pointers to window extensions
	typedef std::vector<UniquePtr<WindowExtension>> EXTENSIONS_VECTOR;


	// window members

	// contains the handle to the child class' window instance
	HWND hwnd;

	// contains the child class' window class identifier
	LPCWSTR className;

	// contains a handle to a mutex previously defined during window binding.
	// if no window was previously bound with a mutex, this defaults to NULL.
	HANDLE hMutex;

	// records the current dimensions of the displayed window
	UINT width, height;


	// messaging

	// pointer to shared message broker
	MessageBroker* broker;

	// specifies if the shared message broker is external or internal. if
	// internal, it must be deallocated on window destruction.
	bool ownsBroker;


	// private methods

	// =======================================================================
	// asserts that the child window class derives from the base window class 
	// correctly, according to the curiously-recurring-template pattern (crtp)
	// =======================================================================
	void assertValidCRTP()
	{
		static_assert(
			std::is_base_of<Window, ChildWindow>::value,
			"Assertion Error: ChildWnd should be a child of BaseWindow!"
		);
	}

protected:

	// protected extension members

	// internal extensions container
	EXTENSIONS_VECTOR extensions;


	// protected methods

	// =======================================================================
	// base window message handler - delegates messages to extensions, then
	// the child window's wndproc, in that sequence
	// =======================================================================
	static LRESULT CALLBACK baseWndProc(
		HWND	hwnd,
		UINT	msg,
		WPARAM	wParam,
		LPARAM	lParam
	) {
		// define pointer to child window instance
		ChildWindow* cWndPtr = NULL;

		// if window is newly created, attempt to cache instance pointer
		if (msg == WM_NCCREATE)
		{
			// cast lParam to CREATESTRUCT ptr as mentioned in the msdn docs
			CREATESTRUCT* pCS = reinterpret_cast<CREATESTRUCT*>(lParam);

			// get pointer to child window from CREATESTRUCT lpCreateParams
			cWndPtr = static_cast<ChildWindow*>(pCS->lpCreateParams);

			// cast child window ptr to long ptr for caching
			LONG_PTR cWndLPtr = reinterpret_cast<LONG_PTR>(cWndPtr);

			// cache child window instance pointer with window data
			SetWindowLongPtr(hwnd, GWLP_USERDATA, cWndLPtr);
		}

		// else, retrieve cached instance pointer from window data
		else
		{
			cWndPtr = reinterpret_cast<ChildWindow*>(
				GetWindowLongPtr(hwnd, GWLP_USERDATA)
			);
		}

		// ensure pointer and hwnd have been initialized
		if (!cWndPtr || !cWndPtr->hwnd)
		{
			// else, run default window message handlers
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}

		// ! start wndproc delegate flow
		Flow<LRESULT> flow(NULL);

		// ! call extensions

		// initialize iterator
		EXTENSIONS_VECTOR::iterator it = cWndPtr->extensions.begin();

		// loop through all extensions from start to end
		while (it != cWndPtr->extensions.end() && flow.stillRunning())
		{
			// run extension wndproc with flow control
			(**it).wndProc(msg, wParam, lParam, flow);

			// increment iterator
			it++;
		}

		// ! call child window wndproc
		if (flow.stillRunning())
		{
			// delegate message to child window wndproc
			flow.update(cWndPtr->wndProc(msg, wParam, lParam));
		}

		// ! handle convenience behaviours

		// update instance count on window destruction
		if (msg == WM_NCDESTROY) cWndPtr->decrementWindows();

		// notify others on window resize
		if (msg == WM_SIZE) {

			// update states
			cWndPtr->updateWidth(LOWORD(lParam));
			cWndPtr->updateHeight(HIWORD(lParam));

			// send window resized notification
			cWndPtr->broker
				->pushImmediately(WindowResized(
					cWndPtr->getHwnd(),
					cWndPtr->getWidth(),
					cWndPtr->getHeight()
				));
		}

		// ! end of delegate flow, return result
		return flow.getResult();
	}

	// =======================================================================
	// virtual wndproc to be implemented by child windows
	// =======================================================================
	virtual LRESULT wndProc(
		UINT	msg,
		WPARAM	wParam,
		LPARAM	lParam
	) = 0;

	// =======================================================================
	// registers the extension instance with the current window class. the 
	// incoming extension should be manually allocated such that its lifecycle
	// can be managed by this instance using the 'new' keyword.
	// =======================================================================
	void addExtension(WindowExtension* extensionPtr)
	{
		// ensure that the extension is unique by checking that the type of 
		// the new extension is different from the types within the container

		// initialize iterator
		EXTENSIONS_VECTOR::iterator it = extensions.begin();

		// loop through all extensions from start to end
		while (it != extensions.end())
		{
			// if typeid of extension at iterator is identical, return early
			if (typeid(**it) == typeid(*extensionPtr)) return;

			// increment iterator
			it++;
		}

		// if extension is unique, bind extension to window
		extensionPtr->bindToWindow(this);

		// move extension to container
		extensions.push_back(std::move(extensionPtr));
	}

	// =======================================================================
	// updates the window's recorded width
	// =======================================================================
	void updateWidth(const UINT& newWidth) { width = newWidth; }

	// =======================================================================
	// updates the window's recorded height
	// =======================================================================
	void updateHeight(const UINT& newHeight) { height = newHeight; }

public:

	// =======================================================================
	// constructor
	// =======================================================================
	Window(
		LPCWSTR			lpszClassName,
		MessageBroker*	pSharedBroker	= nullptr,
		LPCWSTR			lpszMenuName	= D_LPSZMENUNAME,
		UINT			style			= D_STYLE,
		HBRUSH			hbrBackground	= D_HBRUSH,
		HICON			hIcon			= D_HICON,
		HICON			hIconSm			= D_HICON_SM,
		HCURSOR			hCursor			= D_HCURSOR
	) :
		// window states
		hwnd		(NULL),
		className	(lpszClassName),
		hMutex		(NULL),
		width		(SETTINGS_NS::WND_INIT_WIDTH),
		height		(SETTINGS_NS::WND_INIT_HEIGHT),
		broker		(pSharedBroker)
	{
		// statically assert that ChildWnd adheres to CRTP
		assertValidCRTP();

		// check if a shared broker was provided
		ownsBroker = broker == nullptr;

		// if none was provided, manually allocate a new message broker
		if (ownsBroker) broker = new MessageBroker();

		// initialize window class info struct
		WNDCLASSEXW	wcx{};

		// set wcx size
		wcx.cbSize			= sizeof(wcx);

		// don't allocate extra memory for window
		wcx.cbClsExtra		= 0;
		wcx.cbWndExtra		= 0;

		// fill in wcx info using args
		wcx.style			= style;
		wcx.hIcon			= hIcon;
		wcx.hCursor			= hCursor;
		wcx.hbrBackground	= hbrBackground;
		wcx.lpszMenuName	= lpszMenuName;
		wcx.lpszClassName	= lpszClassName;
		wcx.hIconSm			= hIconSm;

		// set instance handle to the current application
		wcx.hInstance		= GetModuleHandle(NULL);
		
		// bind windproc
		wcx.lpfnWndProc		= baseWndProc;

		// register window class from wcx struct
		RegisterClassExW(&wcx);
	}

	// =======================================================================
	// destructor
	// =======================================================================
	~Window()
	{
		// free broker from memory when the window is killed if it's not an
		// external resource but is owned by this instance
		if (ownsBroker) SAFE_DELETE(broker);
	}


	// methods

	// =======================================================================
	// creates a new window instance, binding it to the window class. only one
	// window instance can be bound to a window class at any one time.
	// =======================================================================
	bool bindWindow(
		LPCWSTR	lpWindowName,
		LPCWSTR	mutexName		= D_MUTEXNAME,
		RECT	windowBounds	= RECT{
										SETTINGS_NS::WND_INIT_X,
										SETTINGS_NS::WND_INIT_Y,
										SETTINGS_NS::WND_INIT_WIDTH,
										SETTINGS_NS::WND_INIT_HEIGHT
		},
		HWND	hWndParent		= D_HWNDPARENT,
		HMENU	hMenu			= D_HMENU,
		DWORD	dwStyle			= D_DWSTYLE,
		DWORD	dwExStyle		= D_DWEXSTYLE
	) {
		// ensure no other window is currently bound to this instance
		if (hwnd) return false;

		// ensure that a window can be registered for the specified mutex name
		if (mutexName && !registerWindowMutex(mutexName)) return false;

		// all checks pass, attempt to create and bind new window instance
		hwnd = CreateWindowExW(
			dwExStyle,
			className,
			lpWindowName,
			dwStyle,
			windowBounds.left,
			windowBounds.top,
			windowBounds.right,
			windowBounds.bottom,
			hWndParent,
			hMenu,
			GetModuleHandle(NULL),
			this
		);

		// ensure that window has been created and bound successfully
		if (!hwnd) return false;

		// if successful, present and paint window
		ShowWindow(hwnd, SW_SHOW);
		UpdateWindow(hwnd);

		// increment instance count
		incrementWindows();

		// return success
		return true;
	}

	void killWindow()
	{
		// if no instance is currently bound, exit early
		if (!hwnd) return;

		// temporarily suspend instance counter to avoid auto-quit trigger
		toggleWindowCounter(false);

		// destroy bound window & reset hwnd
		DestroyWindow(hwnd);
		hwnd = NULL;

		// finally, re-enable instance counter
		toggleWindowCounter(true);
	}

	// =======================================================================
	// registers a window instance for the specified mutex
	// =======================================================================
	bool registerWindowMutex(const LPCWSTR& mutexName)
	{
		// initialize last error to null to ensure consistency
		SetLastError(NULL);

		// attempt to make handle with mutexName
		HANDLE hMutexRes = CreateMutexW(NULL, true, mutexName);

		// if mutex handle is NULL, an internal error has occurred!
		// TODO: ERROR LOGGING
		if (hMutexRes == NULL) return false;

		// if the last error returned is ERROR_ALREADY_EXISTS, an instance has
		// already been created for the specified mutex.
		if (GetLastError() == ERROR_ALREADY_EXISTS) return false;

		// otherwise, no instance exists for the specified mutex, registration
		// is successful!
		return true;
	}

	// =======================================================================
	// deregisters the mutex for the currently bound window instance (if
	// previously bound to a mutex)
	// =======================================================================
	void deregisterWindowMutex()
	{
		// if instance was bound to a mutex
		if (hMutex) {

			// attempt to release mutex on a best effort basis
			ReleaseMutex(hMutex);

			// reset bound mutex handle to null
			hMutex = NULL;
		}
	}


	// convenience methods

	// =======================================================================
	// presents and redraws the currently bound window instance in the
	// specified presentation mode
	// =======================================================================
	void updatePresentationMode(const int& nCmdShow)
	{
		// ensure hwnd exists
		if (hwnd) {

			// present window in new presentation mode
			ShowWindow(hwnd, nCmdShow);

			// redraw window
			UpdateWindow(hwnd);
		}
	}

	// =======================================================================
	// shows the currently bound window instance
	// =======================================================================
	void show() { updatePresentationMode(SW_SHOWNORMAL); }

	// =======================================================================
	// hides the currently bound window instance
	// =======================================================================
	void hide() { updatePresentationMode(SW_HIDE); }

	// =======================================================================
	// presents the currently bound window instance in fullscreen
	// =======================================================================
	void maximize() { updatePresentationMode(SW_MAXIMIZE); }

	// =======================================================================
	// sends the currently bound window instance to the task bar
	// =======================================================================
	void minimize() { updatePresentationMode(SW_MINIMIZE); }


	// getters

	// =======================================================================
	// returns the handle to the currently bound window instance
	// =======================================================================
	HWND getHwnd() const { return hwnd; }

	// =======================================================================
	// returns a pointer to the handle to the currently bound window instance
	// =======================================================================
	HWND* getHwndPtr() { return &hwnd; }

	// =======================================================================
	// returns the name of this window class
	// =======================================================================
	LPCWSTR getClassName() const { return className; }

	// =======================================================================
	// returns the recorded width of the window
	// =======================================================================
	UINT getWidth() const { return width; }

	// =======================================================================
	// returns the recorded height of the window
	// =======================================================================
	UINT getHeight() const { return height; }

	// =======================================================================
	// returns a reference to the shared window command broker
	// =======================================================================
	MessageBroker* getBroker() { return broker; }

};

#endif // !_ORBIT_WINDOW_WINDOW_H