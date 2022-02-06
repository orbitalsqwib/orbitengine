// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Style Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTSTYLEOPERATOR_H
#define _ORBIT_GRAPHICS_TEXTSTYLEOPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "textStyleData.h"
#include "../dximport.h"
#include "../graphicsContext.h"
#include "../graphicsOperator.h"
#include <utility>


// main definition

// specifies an object that operates on pure text style data objects, and is
// responsible for handling text style logic
class TextStyleOperator : public GraphicsOperator
{
public:

	// constructor
	TextStyleOperator(GraphicsContext* _context);


	// methods

	// creates a font resource from the fontname specified by the text data 
	// and binds it to the text's font resource pointer.
	void loadResource(TextStyleData& textStyle);

	// releases the font resource at the text style's resource pointer
	void releaseResource(TextStyleData& textStyle);

	// resets the font resource at the text style's resource pointer
	void resetResource(TextStyleData& textStyle);

	// calculates textbox bounds required to fit text based on textStyle
	RECT&& calculateBounds(
		const std::string&		text,
		const TextStyleData&	textStyle
	);

	// calculates textbox width required to fit text based on textStyle
	int calculateWidth(
		const std::string&		text,
		const TextStyleData&	textStyle
	);

	// calculates textbox height required to fit text based on textStyle
	int calculateHeight(
		const std::string&		text,
		const TextStyleData&	textStyle
	);

};

#endif // !_ORBIT_GRAPHICS_TEXTSTYLEOPERATOR_H