// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Style Manager Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTSTYLEMANAGER_H
#define _ORBIT_GRAPHICS_TEXTSTYLEMANAGER_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "textStyleData.h"
#include "textStyleOperator.h"
#include "../../common/commands/graphicsObjectCommands.h"
#include "../../messaging/pubsub.h"
#include <vector>
#include <unordered_map>


// main definition

// manages the lifecycle and logic of text style data objects, and ensures 
// that all font resources are appropriately released or reset according to  
// the graphics context.
class TextStyleManager :  public ISubscriber<GraphicsObjectCommands>
{
private:

	// typedefs

	// specifies a mapping from string identifiers to texture data objects
	typedef std::unordered_map<std::string, TextStyleData> TEXTSTYLE_MAP;


	// members

	// contains a map of string identifiers to texture data objects - pointers
	// to texture data remain valid until erased (which should not happen
	// until the texture manager is destroyed)
	TEXTSTYLE_MAP textStyleMap;

	// texture operator - performs logic on internal textures
	TextStyleOperator textStyleOp;


	// private methods

	// releases resources for all managed textures
	void releaseAllGraphics();

	// resets resources for all managed textures
	void resetAllGraphics();

public:

	// constructor
	TextStyleManager(GraphicsContext* context);


	// methods

	// adds a texture to the texture map for the specified texture name
	TextStyleManager& addTextStyle(
		const std::string&		textStyleName,
		const TextStyleData&	textStyle
	);


	// message handlers

	// handles incoming graphics object commands and performs operations on
	// texture data objects accordingly
	virtual void handleMessage(
		GraphicsObjectCommands	message,
		MessageBroker* broker
	);


	// getters

	// returns a pointer to the text style data for the specified text style
	// name. if no texture data is found, the return value is nullptr.
	TextStyleData* getTextStyleData(const std::string& textStyleName);

};

#endif // !_ORBIT_GRAPHICS_TEXTSTYLEMANAGER_H