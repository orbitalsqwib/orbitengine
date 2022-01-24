// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Text Style Manager Class Implementation
// ===========================================================================

// import specification
#include "textStyleManager.h"


// ===========================================================================
// constructor
// ===========================================================================
TextStyleManager::TextStyleManager(
	GraphicsContext*	context
):
	// members
	textStyleMap	(),
	textStyleOp		(context)
{
	// subscribe self to graphics context broker (if it exists)
	if (MessageBroker* broker = context->getBroker())
	{
		broker->addSubscriber(*this);
	}
}


// private methods

// ===========================================================================
// releases resources for all managed textures
// ===========================================================================
void TextStyleManager::releaseAllGraphics()
{
	// create texture map iterator
	TEXTSTYLE_MAP::iterator it = textStyleMap.begin();

	// iterate through all textures in map
	while (it != textStyleMap.end())
	{
		// reinitialize resources for texture at iterator
		textStyleOp.releaseResource(it->second);

		// increment operator
		it++;
	}
}

// ===========================================================================
// resets resources for all managed textures
// ===========================================================================
void TextStyleManager::resetAllGraphics()
{
	// create texture map iterator
	TEXTSTYLE_MAP::iterator it = textStyleMap.begin();

	// iterate through all textures in map
	while (it != textStyleMap.end())
	{
		// reinitialize resources for texture at iterator
		textStyleOp.resetResource(it->second);

		// increment operator
		it++;
	}
}


// methods

// ===========================================================================
// adds a texture to the texture map for the specified texture name
// ===========================================================================
TextStyleManager& TextStyleManager::addTextStyle(
	const std::string&		textStyleName,
	const TextStyleData&	textStyle
) {
	// check if texture exists for texture name, throw warning if true
	if (textStyleMap.count(textStyleName) > 0) throw Error(
		"Warning: Texture already exists for textureName: " + textStyleName,
		ErrorType::WARNING
	);

	// if it does not exist, add the texture to the texture map
	textStyleMap[textStyleName] = textStyle;

	// load texture data on registration
	textStyleOp.loadResource(textStyleMap[textStyleName]);

	return *this;
}

// ===========================================================================
// handles incoming graphics object commands and performs operations on
// texture data objects accordingly
// ===========================================================================
void TextStyleManager::handleMessage(
	GraphicsObjectCommands	message,
	MessageBroker*			broker
) {
	// handle messages accordingly
	switch (message)
	{
	// should release all managed texture resources
	case GraphicsObjectCommands::RELEASE_ALL_GRAPHICS:
		releaseAllGraphics();
		break;
	
	// should reset all managed texture resources
	case GraphicsObjectCommands::RESET_ALL_GRAPHICS:
		resetAllGraphics();
		break;
	}
}

// ===========================================================================
// returns a pointer to the texture data for the specified texture name
// if no texture data is found, the return value is nullptr.
// ===========================================================================
TextStyleData* TextStyleManager::getTextStyleData(
	const std::string&	textureName
) {
	// if no texture can be found for the texture name, return nullptr
	if (textStyleMap.count(textureName) == 0) return nullptr;

	// else, return pointer to texture for texture name
	return &textStyleMap[textureName];
}