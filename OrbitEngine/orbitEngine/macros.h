// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Common Macros Specification
// ===========================================================================

#ifndef _ORBIT_MACROS_H
#define _ORBIT_MACROS_H

// import windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>


// ===========================================================================
// common macros
// ===========================================================================

// safely delete pointer referenced object
#define SAFE_DELETE(ptr) { if(ptr) { delete(ptr);	ptr = NULL; } }

// safely release pointer referenced object
#define SAFE_RELEASE(ptr) { if(ptr && *ptr) { ptr->Release(); ptr = NULL; } }

// safely delete pointer referenced array
#define SAFE_DELETE_ARRAY(ptr) { if(ptr) { delete [](ptr); ptr = NULL; } }

#endif // !_ORBIT_MACROS_H