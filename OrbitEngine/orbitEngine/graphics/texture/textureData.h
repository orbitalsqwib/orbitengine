// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Texture Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTUREDATA_H
#define _ORBIT_GRAPHICS_TEXTUREDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"
#include "../../common/colors.h"


// main definition

// specifies information about a texture and is pure state. the logic for all
// operations using these states should be carried out by texture operators
struct TextureData
{
	// members
	LPCWSTR		filepath;	// path to file containing texture data
	COLOR_ARGB	chromaKey;	// defines the chroma key for the texture
	UINT		width;		// pixel width of texture
	UINT		height;		// pixel height of texture
	LP_TEXTURE	resource;	// pointer to texture resource

	// convenience constructor
	TextureData(
		LPCWSTR				_filepath	= L"",
		const COLOR_ARGB&	_chromaKey	= NULL,
		const UINT&			_width		= 0,
		const UINT&			_height		= 0
	):
		filepath	(_filepath),
		chromaKey	(_chromaKey),
		width		(_width),
		height		(_height),
		resource	(nullptr)
	{}
};


#endif // !_ORBIT_GRAPHICS_TEXTUREDATA_H