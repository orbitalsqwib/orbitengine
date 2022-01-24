// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Texture Manager Class Implementation
// ===========================================================================

// import specification
#include "textureManager.h"


// ===========================================================================
// constructor
// ===========================================================================
TextureManager::TextureManager(
	GraphicsContext*	context
):
	// members
	textureMap	(),
	textureOp	(context)
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
void TextureManager::releaseAllGraphics()
{
	// create texture map iterator
	TEXTURE_MAP::iterator it = textureMap.begin();

	// iterate through all textures in map
	while (it != textureMap.end())
	{
		// release resources for texture at iterator
		textureOp.releaseResource(it->second);

		// increment operator
		it++;
	}
}

// ===========================================================================
// resets resources for all managed textures
// ===========================================================================
void TextureManager::resetAllGraphics()
{
	// create texture map iterator
	TEXTURE_MAP::iterator it = textureMap.begin();

	// iterate through all textures in map
	while (it != textureMap.end())
	{
		// reinitialize resources for texture at iterator
		textureOp.loadResource(it->second);

		// increment operator
		it++;
	}
}


// methods

// ===========================================================================
// adds a texture to the texture map for the specified texture name
// ===========================================================================
TextureManager& TextureManager::addTexture(
	const std::string&	textureName,
	const TextureData&	texture
) {
	// check if texture exists for texture name, throw warning if true
	if (textureMap.count(textureName) > 0) throw Error(
		"Warning: Texture already exists for textureName: " + textureName,
		ErrorType::WARNING
	);

	// if it does not exist, add the texture to the texture map
	textureMap[textureName] = texture;

	// load texture data on registration
	textureOp.loadResource(textureMap[textureName]);

	return *this;
}

// ===========================================================================
// handles incoming graphics object commands and performs operations on
// texture data objects accordingly
// ===========================================================================
void TextureManager::handleMessage(
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
TextureData* TextureManager::getTextureData(
	const std::string&	textureName
) {
	// if no texture can be found for the texture name, return nullptr
	if (textureMap.count(textureName) == 0) return nullptr;

	// else, return pointer to texture for texture name
	return &textureMap[textureName];
}