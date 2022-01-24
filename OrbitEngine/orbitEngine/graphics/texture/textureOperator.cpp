// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Texture Operator Class Implementation
// ===========================================================================

// import specification
#include "textureOperator.h"


// ===========================================================================
// constructor
// ===========================================================================
TextureOperator::TextureOperator(
	GraphicsContext*	_context
):
	// base constructor
	GraphicsOperator	(_context)
{}


// methods

// ===========================================================================
// creates a texture resource from the file specified by the texture and
// binds it to the texture's resource pointer.
// ===========================================================================
void TextureOperator::loadResource(
	TextureData&	texture
) {
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// initialize image data container
	D3DXIMAGE_INFO imageInfo;

	// attempt to load texture from file
	try
	{
		// ensure filepath is provided, else throw exception
		if (texture.filepath == NULL) throw Error(
			"Error: Could not retrieve filepath from texture data!"
		);

		// get width and height of texture from file
		res = D3DXGetImageInfoFromFile(texture.filepath, &imageInfo);

		// ensure image data is successfully retrieved
		if (res != D3D_OK) throw Error(
			"Error: Could not retrieve image data from filepath!"
		);

		// update recorded texture dimensions using file info
		texture.width	= imageInfo.Width;
		texture.height	= imageInfo.Height;

		// create the texture resource from the image file
		res = D3DXCreateTextureFromFileExW(
			context->getD3DDevice(),	// get graphics device from context
			texture.filepath,			// image filename
			imageInfo.Width,			// texture width
			imageInfo.Height,			// texture height
			1,							// mip-map levels (1 for no chain)
			0,							// usage (dynamic texture)
			D3DFMT_UNKNOWN,				// surface format (default)
			D3DPOOL_DEFAULT,			// memory class for texture
			D3DX_DEFAULT,				// image filter
			D3DX_DEFAULT,				// mip filter
			texture.chromaKey,			// color key for transparency
			&imageInfo,					// file info (from loaded file)
			NULL,						// color palette
			&texture.resource			// resource pointer destination
		);
	}
	catch (...)
	{
		// throw on error
		throw Error("Error: Failed to load texture from file!");
	}
}

// ===========================================================================
// releases the texture resource at the target's texture resource pointer
// ===========================================================================
void TextureOperator::releaseResource(
	TextureData&	texture
) {
	// safely release target resource (with nullptr check)
	SAFE_RELEASE(texture.resource);
}
