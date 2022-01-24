// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Texture Manager Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_TEXTUREMANAGER_H
#define _ORBIT_GRAPHICS_TEXTUREMANAGER_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "textureData.h"
#include "textureOperator.h"
#include "../../common/commands/graphicsObjectCommands.h"
#include "../../messaging/pubsub.h"
#include <vector>
#include <unordered_map>


// main definition

// manages the lifecycle and logic of texture data objects, and ensures that
// all textures are appropriately released or reset according to the graphics
// context.
class TextureManager : public ISubscriber<GraphicsObjectCommands>
{
private:

	// typedefs

	// specifies a mapping from string identifiers to texture data objects
	typedef std::unordered_map<std::string, TextureData> TEXTURE_MAP;


	// members

	// contains a map of string identifiers to texture data objects - pointers
	// to texture data remain valid until erased (which should not happen
	// until the texture manager is destroyed)
	TEXTURE_MAP textureMap;

	// texture operator - performs logic on internal textures
	TextureOperator textureOp;


	// private methods

	// releases resources for all managed textures
	void releaseAllGraphics();

	// resets resources for all managed textures
	void resetAllGraphics();

public:

	// constructor
	TextureManager(GraphicsContext* context);

	
	// methods

	// adds a texture to the texture map for the specified texture name
	TextureManager& addTexture(
		const std::string&	textureName,
		const TextureData&	texture
	);


	// message handlers

	// handles incoming graphics object commands and performs operations on
	// texture data objects accordingly
	virtual void handleMessage(
		GraphicsObjectCommands	message,
		MessageBroker*			broker
	);

	
	// getters

	// returns a pointer to the texture data for the specified texture name.
	// if no texture data is found, the return value is nullptr.
	TextureData* getTextureData(const std::string& textureName);

};

#endif // !_ORBIT_GRAPHICS_TEXTUREMANAGER_H