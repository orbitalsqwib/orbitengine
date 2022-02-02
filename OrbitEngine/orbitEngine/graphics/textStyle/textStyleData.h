// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Style Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTSTYLEDATA_H
#define _ORBIT_GRAPHICS_TEXTSTYLEDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../dximport.h"
#include "../../common/colors.h"


// main definition

// defines text style data such as font data, highlighting data and the font 
// resource pointer. as a piece of pure state, all logic using these data
// should be carried out by text operators.
struct TextStyleData
{
	// members
	LPCWSTR		fontName;			// name of font
	UINT		fontHeight;			// height of rendered font
	bool		italics;			// specifies if the font is italicized
	bool		bold;				// specifies if the font is bolded
	COLOR_ARGB	fontColor;			// color of rendered font
	COLOR_ARGB	highlightColor;		// color of text highlight
	UINT		highlightPadding;	// additional text highlight padding
	LP_FONT		fontResource;		// font resource pointer

	// convenience constructor
	TextStyleData(
		LPCWSTR				_fontName			= L"OCR A",
		const UINT&			_fontHeight			= 12,
		const bool&			_italics			= false,
		const bool&			_bold				= false,
		const COLOR_ARGB&	_fontColor			= Colors::BLACK,
		const COLOR_ARGB&	_highlightColor		= Colors::ALPHA0,
		const UINT&			_highlightPadding	= 3
	):
		fontName			(_fontName),
		fontHeight			(_fontHeight),
		italics				(_italics),
		bold				(_bold),
		fontColor			(_fontColor),
		highlightColor		(_highlightColor),
		highlightPadding	(_highlightPadding),
		fontResource		(nullptr)
	{}
};

#endif // !_ORBIT_GRAPHICS_TEXTSTYLEDATA_H