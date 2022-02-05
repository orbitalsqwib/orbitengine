// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Border Handler Specification
// ===========================================================================

#ifndef _STV_HANDLERS_BORDER_H
#define _STV_HANDLERS_BORDER_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "../../orbitEngine/imports/graphics.h"
#include "../../orbitEngine/imports/commons.h"


// main definition

// defines and manages the game border
class Border
{
private:

	// members

	// specifies the horizontal padding between the screen edge and the border
	float xPadding;

	// specifies the vertical padding between the screen edge and the border
	float yPadding;

	// specifies the border color
	COLOR_ARGB color;

	// pointer reference to graphics context
	GraphicsContext* graphics;

	// initialization flag
	bool initialized;

public:

	// constructor
	Border():

		// members
		xPadding	(0),
		yPadding	(0),
		color		(Colors::RED),
		graphics	(nullptr),
		initialized	(false)
	{}

	// initializer
	void initialize(
		const float&		_xPadding,
		const float&		_yPadding,
		GraphicsContext&	_graphics
	) {
		// update states
		xPadding = _xPadding;
		yPadding = _yPadding;
		graphics = &_graphics;

		// update initialization flag
		initialized = true;
	}


	// methods

	// returns the corners for the border rect
	FloatRect getCorners()
	{
		return(FloatRect(
			xPadding,
			yPadding,
			graphics->getDisplayWidth() - xPadding,
			graphics->getDisplayHeight() - yPadding
		));
	}

	// renders the border instance
	void render()
	{
		// ensure border has been initialized
		if (!initialized) throw Error("Error: Border not initialized!");

		// calculate border corners
		FloatRect c = getCorners();

		// set up vertex buffers for border outline
		Vertex vertices[5]
		{
			Vertex(c.left  , c.top    , ZValues::OVERLAYS, color, 0.0f, 0.0f),
			Vertex(c.right , c.top    , ZValues::OVERLAYS, color, 1.0f, 0.0f),
			Vertex(c.right , c.bottom , ZValues::OVERLAYS, color, 1.0f, 1.0f),
			Vertex(c.left  , c.bottom , ZValues::OVERLAYS, color, 0.0f, 1.0f),
			Vertex(c.left  , c.top    , ZValues::OVERLAYS, color, 0.0f, 0.0f)
		};

		// draw vertices
		if (graphics->beginSpriteDraw() == D3D_OK)
		{
			graphics->drawVertices(vertices, 5, D3DPT_LINESTRIP, 4);
			graphics->endSpriteDraw();
		}
	}

	// sets the xPadding of the border
	void setXPadding(const float& _newVal) { xPadding = _newVal; }

	// sets the yPadding of the border
	void setYPadding(const float& _newVal) { yPadding = _newVal; }

	// sets the color of the border
	void setColor(const COLOR_ARGB& _newVal) { color = _newVal; }
};

#endif // !_STV_HANDLERS_BORDER_H