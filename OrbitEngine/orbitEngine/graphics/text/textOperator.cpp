// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Operator Class Implementation
// ===========================================================================

// import specification
#include "textOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
TextOperator::TextOperator(
	GraphicsContext* _context
) :
	// base constructor
	GraphicsOperator	(_context),

	// members
	shapeOp				(_context),
	textStyleOp			(_context)
{}


// methods

// ===========================================================================
// queues text data to be rendered relative to the specified coordinates.
// should only be called between the graphics context's 
// beginSpriteDraw()...endSpriteDraw() method calls.
// ===========================================================================
void TextOperator::render(
	TextData&		text,
	const UINT&		format
) {
	// ensure font resource exists, else exit early
	if (!text.pStyle || !text.pStyle->fontResource) return;

	// limit z to 0.999 to ensure that highlight doesn't draw over text
	if (text.z > 0.999f) text.z = 0.999f;

	// calculate textbox width and height (updates right, bottom)
	RECT textbox = textStyleOp.calculateBounds(text.text, *text.pStyle);

	// calculate textbox position
	textbox.left	+= static_cast<LONG>(text.x);
	textbox.top		+= static_cast<LONG>(text.y);

	// check if highlight is not fully transparent
	if (text.pStyle->highlightColor & Colors::ALPHAMASK) {

		// draw highlight rect "behind text"
		shapeOp.render(
			ShapeData(
				BasicShape::RECTANGLE,
				static_cast<float>(textbox.left)			// x
				- text.pStyle->highlightPadding,

				static_cast<float>(textbox.top)				// y
				- text.pStyle->highlightPadding,

				text.z + 0.001f,							// z

				static_cast<float>(textbox.right)			// width
				+ (text.pStyle->highlightPadding << 1),

				static_cast<float>(textbox.bottom)			// height
				+ (text.pStyle->highlightPadding << 1),

				text.pStyle->highlightColor					// color
			)
		);
	}

	// calculate textbox right / bottom actual positions
	textbox.right	+= static_cast<LONG>(text.x);
	textbox.bottom	+= static_cast<LONG>(text.y);

	// apply z translation for text

	D3DXMATRIX temp;
	context->getD3DSprite()->SetTransform(
		D3DXMatrixTranslation(&temp, 0.0f, 0.0f, text.z)
	);

	// draw text
	text.pStyle->fontResource->DrawTextA(
		context->getD3DSprite(),	// sprite object containing string
		text.text.c_str(),			// string to draw
		-1,							// define string as null-terminated
		&textbox,					// rect to draw the text in
		format,						// text formatting methods
		text.pStyle->fontColor		// text color
	);
}