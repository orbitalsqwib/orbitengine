// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Style Operator Class Implementation
// ===========================================================================

// import specification
#include "textStyleOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
TextStyleOperator::TextStyleOperator(
	GraphicsContext*	_context
):
	// base constructor
	GraphicsOperator	(_context)
{}


// methods

// ===========================================================================
// creates a font resource from the fontname specified by the text data 
// and binds it to the text's font resource pointer.
// ===========================================================================
void TextStyleOperator::loadResource(
	TextStyleData&	textStyle,
	const bool&		bold,
	const bool&		italic
) {
	// create directx font resource
	HRESULT res = D3DXCreateFontW(
		context->getD3DDevice(),
		textStyle.fontHeight,
		0,	// scale font size to font height
		bold ? FW_BOLD : FW_NORMAL,
		1,	// mipmap levels should always be 1
		italic,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH | FF_DONTCARE,
		textStyle.fontName,
		&textStyle.fontResource
	);

	// if font creation fails, throw exception
	if (res != D3D_OK) throw Error(
		"Error: Failed to create font resource for font!"
	);
}

// ===========================================================================
// releases the font resource at the text style's resource pointer
// ===========================================================================
void TextStyleOperator::releaseResource(
	TextStyleData&	textStyle
) {
	// if font resource exists, tell it to release reserved memory
	if (textStyle.fontResource) textStyle.fontResource->OnLostDevice();
}

// ===========================================================================
// resets the font resource at the text style's resource pointer
// ===========================================================================
void TextStyleOperator::resetResource(
	TextStyleData&	textStyle
) {
	// if font resource exists, tell it to reacquire initial resources
	if (textStyle.fontResource) textStyle.fontResource->OnResetDevice();
}

// ===========================================================================
// calculates textbox bounds required to fit text based on textStyle
// ===========================================================================
RECT&& TextStyleOperator::calculateBounds(
	const std::string&		text,
	const TextStyleData&	textStyle
) {
	// ensure font resource has been initialized
	if (textStyle.fontResource == NULL) return std::move(RECT{ 0, 0, 0, 0 });

	// temp rect obj that will be automatically resized
	RECT resizeRect({ 0,0,0,0 });

	// update temp rect with new height and widths
	textStyle.fontResource->DrawTextA(
		context->getD3DSprite(),	// sprite object containing string
		text.c_str(),				// string to draw
		-1,							// define string as null-terminated
		&resizeRect,				// rect to draw the text in
		DT_CALCRECT,				// calculate rect bounds
		NULL						// text color
	);

	// return resized bounds
	return std::move(resizeRect);
}

// ===========================================================================
// calculates textbox width required to fit text based on textStyle
// ===========================================================================
int TextStyleOperator::calculateWidth(
	const std::string&		text,
	const TextStyleData&	textStyle
) {
	return calculateBounds(text, textStyle).right;
}

// ===========================================================================
// calculates textbox height required to fit text based on textStyle
// ===========================================================================
int TextStyleOperator::calculateHeight(
	const std::string& text,
	const TextStyleData& textStyle
) {
	return calculateBounds(text, textStyle).bottom;
}
