// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Graphics Handler Class Specification
// ===========================================================================

#ifndef _ORBIT_GRAPHICS_GRAPHICS_H
#define _ORBIT_GRAPHICS_GRAPHICS_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "dximport.h"
#include "primitiveShape.h"
#include "spriteData.h"
#include "vertex.h"
#include "../!config.h"
#include "../error.h"
#include "../common/colors.h"
#include "../common/commands/graphicsObjectCommands.h"
#include "../common/notifications/windowResized.h"
#include "../messaging/pubsub.h"
#include <assert.h>


// main definition
class GraphicsHandler : ISubscriber<WindowResized>
{
private:

	// display states

	// pointer to handle of managed window
	HWND* hWndPtr;

	// backbuffer display dimensions
	UINT bbWidth, bbHeight;

	// specifies if the handler should use directx fullscreen
	bool fullscreen;

	// default background display color
	COLOR_ARGB bgColor;


	// directx interface states

	// direct3d interface
	LP_3D direct3d;

	// direct3d device interface
	LP_3DDEVICE device3d;

	// direct3d sprite interface
	LP_SPRITE sprite3d;


	// buffers

	// vertex buffer pointer
	LP_VERTEXBUFFER pVB;

	// records the maximum number of vertices that the vertex buffer can hold
	size_t vbMaxVertices;

	
	// messaging

	// pointer to shared message broker
	MessageBroker* broker;


	// config states

	// specifies the current d3d presentation parameters
	D3DPRESENT_PARAMETERS d3dPP;


	// private initalization methods

	// initializes the direct3d presentation parameters. should only be called
	// on initialization or when display states have been updated, which will
	// reset the swap chain for the graphics handler.
	void initializeD3DPP();

	// creates a direct3d device and binds it to the device3d interface
	void initializeDevice3D();

	// creates a direct3d sprite object and binds it to the sprite3d interface
	void initializeSprite3D();


	// private vertex buffer methods

	// initializes a fixed size vertex buffer that will be reused for each
	// primitive drawing task. this buffer may be recreated with a larger size
	// using the resizeVB() method. (default size = 128 vertices)
	void initializeVB(size_t maxVertices = 128);

	// frees the current vertex buffer from memory
	void releaseVB();


	// private device management methods

	// checks if the current state of the direct3d device is valid
	HRESULT checkDeviceState();

	// resets the direct3d device - this should be called when the graphics
	// device is in an invalid / lost state, or when the device's presentation
	// parameters should be updated.
	void resetDevice();

public:

	// constructor
	GraphicsHandler();

	// destructor
	~GraphicsHandler();


	// basic methods

	// initializes the graphics handler instance, binding it to a window.
	void initialize(
		HWND*		_hWndPtr,
		const UINT& _backBufferWidth,
		const UINT& _backBufferHeight,
		const bool	_fullscreen
	);

	// clears the backbuffer and initiates the directx scene drawing sequence.
	// all renderables should be queued for rendering after this function is
	// called, up until endSceneDraw() is called.
	HRESULT beginSceneDraw();

	// ends the directx scene drawing sequence. once this is called, all 
	// renderables queued will be passed to the driver for rendering.
	HRESULT endSceneDraw();

	// swaps the back-buffer with the currently displayed frame buffer,
	// displaying it. (page-flipping)
	HRESULT showBackBuffer();

	// checks if the current state of the direct3d device is valid. if it is
	// not, handles the necessary procedures to recover the device. should be
	// called frequently, optimally every update frame.
	void maintainDevice();


	// sprite drawing methods

	// prepares the direct3d device for drawing sprites. marks the start of
	// the directx sprite drawing sequence, and should only be called between
	// a beginSceneDraw()...endSceneDraw() method pair.
	void beginSpriteDraw();

	// ends the directx sprite drawing sequence, and submits all batched
	// sprites to the device to be rendered. should only be called between a
	// beginSceneDraw()...endSceneDraw() method pair, after beginSpriteDraw()
	// has been invoked.
	void endSpriteDraw();

	// creates a texture resource from a file and saves a reference to it 
	// to a texture resource pointer.
	HRESULT loadTexture(
		LPCWSTR			filename,
		COLOR_ARGB		chromaKey,
		UINT&			textureWidthOut,
		UINT&			textureHeightOut,
		LP_TEXTURE&		pTextureOut
	);

	// queues a sprite to be drawn with the texture and transforms specified
	// by a spriteData struct. should only be called between a
	// beginSpriteDraw()...endSpriteDraw() method pair.
	void drawSprite(
		const SpriteData&	spriteData,
		COLOR_ARGB			color
	);


	// primitive drawing methods

	// re-initializes the vertex buffer to a different size, freeing the 
	// previous vertex buffer from memory. (default size = 128 vertices)
	void resizeVB(size_t maxVertices = 128);

	// draws a set of vertices as the specified primitiveType. the number of 
	// vertices should not exceed the maximum number of vertices that can
	// be stored within the currently allocated vertex buffer.
	void drawVertices(
		Vertex				vertices[],
		size_t				nVertices,
		D3DPRIMITIVETYPE	primitiveType,
		size_t				nPrimitives
	);

	// convenience method - wraps drawVertices() for primitive shape structs
	template <size_t nVertices>
	void drawPrimitive(const PrimitiveShape<nVertices>& shape);


	// message handlers

	// handles the window resized notification by updating the presentation
	// parameters for the graphics handlers. note that this will reset the 
	// directx device in the process.
	virtual void handleMessage(
		WindowResized	message,
		MessageBroker*	broker
	);


	// getters

	// return a pointer to the direct3d interface
	LP_3D getDirect3D() { return direct3d; }

	// return a pointer to the direct3d device interface
	LP_3DDEVICE getD3DDevice() { return device3d; }

	// return a pointer to the direct3d sprite interface
	LP_SPRITE getD3DSprite() { return sprite3d; }

	// return the handle to the current window
	HWND getHwnd() const { return *hWndPtr; }

	// return the handle to the direct3d device context for the current window
	HDC getDC() { return GetDC(getHwnd()); }

	// returns the backbuffer frame's width - this should be used as the
	// canonical display width in any graphics calculations
	UINT getDisplayWidth() { return bbWidth; }

	// returns the backbuffer frame's height - this should be used as the
	// canonical display height in any graphics calculations
	UINT getDisplayHeight() { return bbHeight; }

	// return a pointer to the current vertex buffer pointer
	LP_VERTEXBUFFER* getPPVB() { return &pVB; }


	// setters

	// updates the background color for the backbuffer
	void setBGColor(const COLOR_ARGB& color) { bgColor = color; }

};

#endif // !_ORBIT_GRAPHICS_GRAPHICS_H