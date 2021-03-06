// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : DirectX Imports and Macros
// ===========================================================================
// NOTE: If d3dx9.h is NOT FOUND, go to Properties > VC++ Directories and add
// $(DXSDK_DIR)Include and $(DXSDK_DIR)Lib\x86 into Include Directories and
// Library Directories respectively
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_DXMACROS_H
#define _ORBIT_GRAPHICS_DXMACROS_H

// include intellisense warnings
#include <CodeAnalysis/Warnings.h>

// define verbose debug info for d3dx9
#define D3D_DEBUG_INFO

// import d3d9 header and libraries (suppresses warnings from libraries)
#pragma warning(push)
#pragma warning(disable: ALL_CODE_ANALYSIS_WARNINGS )
#include <d3d9.h>
#include <d3dx9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma warning(pop)

// directx interface aliases
#define LP_TEXTURE		LPDIRECT3DTEXTURE9
#define LP_SPRITE		LPD3DXSPRITE
#define LP_3DDEVICE		LPDIRECT3DDEVICE9
#define LP_3D			LPDIRECT3D9
#define LP_FONT			LPD3DXFONT
#define LP_VERTEXBUFFER LPDIRECT3DVERTEXBUFFER9

#endif // !_ORBIT_GRAPHICS_DXMACROS_H