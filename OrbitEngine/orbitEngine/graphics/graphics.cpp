// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Graphics Handler Class Implementation
// ===========================================================================

// import specification
#include "graphics.h"


// ===========================================================================
// constructor
// ===========================================================================
GraphicsHandler::GraphicsHandler():

	// display states
	hWndPtr			(nullptr),
	bbWidth			(SETTINGS_NS::WND_INIT_WIDTH),
	bbHeight		(SETTINGS_NS::WND_INIT_HEIGHT),
	fullscreen		(false),
	bgColor			(Colors::LIME),

	// directx interface pointers
	direct3d		(nullptr),
	device3d		(nullptr),
	sprite3d		(nullptr),

	// buffers
	pVB				(nullptr),
	vbMaxVertices	(0),

	// messaging
	broker			(nullptr),

	// config states
	d3dPP			()
{}

// ===========================================================================
// destructor
// ===========================================================================
GraphicsHandler::~GraphicsHandler()
{
	// release all interfaces
	SAFE_RELEASE(direct3d);
	SAFE_RELEASE(device3d);
	SAFE_RELEASE(sprite3d);

	// release vertex buffer
	releaseVB();
}


// private initalization methods

// ===========================================================================
// initializes the direct3d presentation parameters. should only be called
// on initialization or when display states have been updated, which will
// reset the swap chain for the graphics handler.
// ===========================================================================
void GraphicsHandler::initializeD3DPP()
{
	assert(hWndPtr != NULL);
	try
	{
		// initialize presentation parameters
		ZeroMemory(&d3dPP, sizeof(d3dPP));

		// configure presentation parameters

		// ! set backbuffer dimensions
		d3dPP.BackBufferWidth	= bbWidth;
		d3dPP.BackBufferHeight	= bbHeight;

		// ! set backbuffer framebuffers -> single-buffered
		d3dPP.BackBufferCount	= 1;		

		// ! set backbuffer format
		d3dPP.BackBufferFormat	= fullscreen 
								? D3DFMT_X8R8G8B8 
								: D3DFMT_UNKNOWN;

		// ! set backbuffer swap behaviour
		d3dPP.SwapEffect		= D3DSWAPEFFECT_DISCARD;

		// ! set display mode
		d3dPP.Windowed			= !fullscreen;

		// ! set output window
		d3dPP.hDeviceWindow		= *hWndPtr;

		// ! set presentation interval
		d3dPP.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

		// ! turn on z-buffering
		d3dPP.EnableAutoDepthStencil	= TRUE;
		d3dPP.AutoDepthStencilFormat	= D3DFMT_D16;
	}
	catch (...)
	{
		throw Error(
			"Error: Failed to initialize Direct3D presentation parameters!"
		);
	}
}

// ===========================================================================
// creates a direct3d device and binds it to the device3d interface
// ===========================================================================
void GraphicsHandler::initializeDevice3D()
{
	assert(hWndPtr != NULL);

	// initialize device3d presentation parameters
	initializeD3DPP();

	// create result container
	HRESULT res;

	// define default device behaviour flags
	DWORD behaviour = D3DCREATE_SOFTWARE_VERTEXPROCESSING;

	// determine if graphics card supports necessary features like hardware
	// texturing, lighting and vertex shaders in preparation for creating a
	// d3d device.

	// initialize device information struct
	D3DCAPS9 caps;

	// retrieve information about device and write the output to caps
	res = direct3d->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps);

	// check if hardware processing is enabled
	bool hw_enabled = (res == D3D_OK)
		&& caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT
		|| caps.VertexShaderVersion >= D3DVS_VERSION(1, 1);

	// if hardware processing is enabled, update behaviour to match
	if (hw_enabled) behaviour = D3DCREATE_HARDWARE_VERTEXPROCESSING;

	// initialize device3d
	res = direct3d->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		*hWndPtr,
		behaviour,
		&d3dPP,
		&device3d
	);

	// ensure d3d device is successfully initialized
	if (FAILED(res)) throw Error(
		"Error: Failed to initialize Direct3D device interface!"
	);
}

// ===========================================================================
// creates a direct3d sprite object and binds it to the sprite3d interface
// ===========================================================================
void GraphicsHandler::initializeSprite3D()
{
	// create the d3d sprite object and bind it to the sprite3d interface
	if (D3DXCreateSprite(device3d, &sprite3d) != D3D_OK) {

		// throw error on failure
		throw Error(
			"Error: Failed to initialize Direct3D Sprite interface!"
		);
	}
}


// private vertex buffer methods

// ===========================================================================
// initializes a fixed size vertex buffer that will be reused for each
// primitive drawing task. this buffer may be recreated with a larger size
// using the resizeVB() method. (default size = 128 vertices)
// ===========================================================================
void GraphicsHandler::initializeVB(
	size_t	maxVertices
) {
	// create result container
	HRESULT res {};

	// attempt to create vertex buffer
	device3d->CreateVertexBuffer(
		maxVertices * sizeof(Vertex),	// specify vertex buffer size
		D3DUSAGE_DYNAMIC,				// dynamic usage flag (AGP memory)
		D3DFVF_Vertex,					// custom vertex format
		D3DPOOL_DEFAULT,				// use most appropriate memory pool
		&pVB,							// destination vertex buffer pointer
		NULL							// don't share resources
	);

	// ensure vertex buffer created successfully, else throw error
	if (res != D3D_OK) throw Error(
		"Error: Failed to initialize graphics vertex buffer!"
	);

	// update max vertices for vertex buffer
	vbMaxVertices = maxVertices;

	// set stream source and fvf format for future primitive drawing
	device3d->SetStreamSource(0, pVB, 0, sizeof(Vertex));
	device3d->SetFVF(D3DFVF_Vertex);
}

// ===========================================================================
// frees the current vertex buffer from memory
// ===========================================================================
void GraphicsHandler::releaseVB()
{
	// release vertex buffer
	SAFE_RELEASE(pVB);

	// reset max vertices to 0
	vbMaxVertices = 0;
}


// private device management methods

// ===========================================================================
// checks if the current state of the direct3d device is valid
// ===========================================================================
HRESULT GraphicsHandler::checkDeviceState()
{
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// ensure that graphics device exists, else exit early
	if (device3d == nullptr) return res;

	// get status of device
	res = device3d->TestCooperativeLevel();

	// return status
	return res;
}

// ===========================================================================
// resets the direct3d device - this should be called when the graphics
// device is in an invalid / lost state, or when the device's presentation
// parameters should be updated.
// ===========================================================================
void GraphicsHandler::resetDevice()
{
	// notify all relevant subscribers to release their resources 
	// immediately, in preparation for device reset
	if (broker) broker->pushImmediately(
		GraphicsObjectCommands::RELEASE_ALL_GRAPHICS
	);

	// re-initialise device presentation parameters
	initializeD3DPP();

	// attempt to reset graphics device - if reset fails, try again next time
	if (device3d->Reset(&d3dPP) != D3D_OK) return;

	// if reset succeeds, notify all relevant subscribers to re-initialize
	// or re-acquire their resources immediately
	if (broker) broker->pushImmediately(
		GraphicsObjectCommands::RESET_ALL_GRAPHICS
	);
}


// basic methods

// ===========================================================================
// initializes the graphics handler instance, binding it to a window.
// ===========================================================================
void GraphicsHandler::initialize(
	HWND*		_hWndPtr,
	const UINT&	_backBufferWidth,
	const UINT&	_backBufferHeight,
	const bool	_fullscreen
) {
	// ensure that hWndPtr is valid
	if (hWndPtr == nullptr) throw Error(
		"Error: Graphics Handler is not bound to a window!"
	);

	// update states
	hWndPtr		= _hWndPtr;
	bbWidth		= _backBufferWidth;
	bbHeight	= _backBufferHeight;
	fullscreen	= _fullscreen;

	// initialize direct3d
	direct3d = Direct3DCreate9(D3D_SDK_VERSION);

	// ensure direct3d has been properly initialized
	if (direct3d == nullptr) throw Error(
		"Error: Failed to initialize Direct3d!"
	);

	// initialize the device3d interface
	initializeDevice3D();

	// initialize the sprite3d interface
	initializeSprite3D();

	// initialize the vertex buffer with default max vertices
	initializeVB();
}

// ===========================================================================
// clears the backbuffer and initiates the directx scene drawing sequence.
// all renderables should be queued for rendering after this function is
// called, up until endSceneDraw() is called.
// ===========================================================================
HRESULT GraphicsHandler::beginSceneDraw()
{
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// ensure graphics device exists, else exit early
	if (device3d == nullptr) return res;

	// reset the entire back-buffer and z-buffer, initializing them to bgColor
	device3d->Clear(
		0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, bgColor, 1.0f, 0
	);

	// begin the scene drawing sequence
	res = device3d->BeginScene();

	// setup view/projection transforms

	// ! initialize view transform matrix
	D3DXMATRIX viewTransform;

	// ! define view transform matrix parameters
	D3DXVECTOR3 eyePos	{ 0.0f, 0.0f, 10.0f };	// eye position
	D3DXVECTOR3 atPos	{ 0.0f, 0.0f,  0.0f };	// camera look-at target
	D3DXVECTOR3 upDir	{ 0.0f, 1.0f,  0.0f };	// world "up" direction

	// ! construct view transform matrix
	D3DXMatrixLookAtLH(
		&viewTransform,
		&eyePos,
		&atPos,
		&upDir
	);

	// ! initialize projection transform matrix
	D3DXMATRIX projectionTransform;

	// ! construct projection transform matrix
	D3DXMatrixPerspectiveFovLH(
		&projectionTransform,
		D3DXToRadian(45),				// specifies a 45 degree FOV
		static_cast<float>(bbWidth) /	// calculates the screen aspect ratio
		static_cast<float>(bbHeight),
		1.0f,							// specifies the near view plane
		1000.0f							// specifies the far view plane
	);

	// apply transforms
	device3d->SetTransform(D3DTS_VIEW, &viewTransform);
	device3d->SetTransform(D3DTS_PROJECTION, &projectionTransform);

	// return result
	return res;
}

// ===========================================================================
// ends the directx scene drawing sequence. once this is called, all 
// renderables queued will be passed to the driver for rendering.
// ===========================================================================
HRESULT GraphicsHandler::endSceneDraw()
{
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// ensure that graphics device exists, else exit early
	if (device3d == nullptr) return res;

	// end the current scene drawing sequence
	res = device3d->EndScene();

	// return result
	return res;
}

// ===========================================================================
// swaps the back-buffer with the currently displayed frame buffer,
// displaying it. (page-flipping)
// ===========================================================================
HRESULT GraphicsHandler::showBackBuffer()
{
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// ensure that graphics device exists, else exit early
	if (device3d == nullptr) return res;

	// display the back-buffer by swapping it with the current frame buffer
	res = device3d->Present(NULL, NULL, NULL, NULL);

	// return status
	return res;
}

// ===========================================================================
// checks if the current state of the direct3d device is valid. if it is
// not, handles the necessary procedures to recover the device. should be
// called frequently, optimally every update frame.
// ===========================================================================
void GraphicsHandler::maintainDevice()
{
	// query device state
	HRESULT deviceState = checkDeviceState();

	// if device state is normal, return early
	if (deviceState == D3D_OK) return;

	// else, handle abnormal status accordingly
	switch (deviceState)
	{
	// device is lost
	case D3DERR_DEVICELOST:
	{
		// reset unavailable at this time - wait and retry on next call
		Sleep(100);
		break;
	}

	// device is available for reset
	case D3DERR_DEVICENOTRESET:
	{
		// attempt to reset device
		resetDevice();
		break;
	}

	// note: other device errors are not handled
	}
}


// sprite drawing methods

// ===========================================================================
// prepares the direct3d device for drawing sprites. marks the start of
// the directx sprite drawing sequence, and should only be called between
// a beginSceneDraw()...endSceneDraw() method pair.
// ===========================================================================
void GraphicsHandler::beginSpriteDraw()
{
	// ensure that the sprite3d interface is valid, else exit early
	if (sprite3d == nullptr) return;

	// inform the sprite3d interface to begin the sprite drawing sequence
	sprite3d->Begin(
		D3DXSPRITE_ALPHABLEND |
		D3DXSPRITE_SORT_DEPTH_FRONTTOBACK
	);
}

// ===========================================================================
// ends the directx sprite drawing sequence, and submits all batched
// sprites to the device to be rendered. should only be called between a
// beginSceneDraw()...endSceneDraw() method pair, after beginSpriteDraw()
// has been invoked.
// ===========================================================================
void GraphicsHandler::endSpriteDraw()
{
	// ensure that the sprite3d interface is valid, else exit early
	if (sprite3d == nullptr) return;

	// inform the sprite3d interface to end the sprite drawing sequence
	sprite3d->End();
}

// ===========================================================================
// creates a texture resource from a file and saves a reference to it 
// to a texture resource pointer.
// ===========================================================================
HRESULT GraphicsHandler::loadTexture(
	LPCWSTR			filename,
	COLOR_ARGB		chromaKey,
	UINT&			textureWidthOut,
	UINT&			textureHeightOut,
	LP_TEXTURE&		pTextureOut
) {
	// create result container and initialize it to fail by default
	HRESULT res = E_FAIL;

	// initialize image data container
	D3DXIMAGE_INFO imageInfo;

	// attempt to load texture from file
	try
	{
		// ensure filename is provided
		if (filename == NULL)
		{
			// if not, fail gracefully and return the appropriate status
			pTextureOut = NULL;
			return E_FAIL;
		}

		// get width and height of texture from file
		res = D3DXGetImageInfoFromFile(filename, &imageInfo);

		// ensure image data is successfully retrieved
		if (res != D3D_OK)
		{
			// if not, fail gracefully and return the appropriate status
			pTextureOut = NULL;
			return res;
		}

		// update references for texture dimensions using file info
		textureWidthOut		= imageInfo.Width;
		textureHeightOut	= imageInfo.Height;

		// create the texture resource from the image file
		res = D3DXCreateTextureFromFileExW(
			device3d,			// the bound d3d device interface
			filename,			// image filename
			imageInfo.Width,	// texture width
			imageInfo.Height,	// texture height
			1,					// mip-map levels (1 for no chain)
			0,					// usage (dynamic texture)
			D3DFMT_UNKNOWN,		// surface format (default)
			D3DPOOL_DEFAULT,	// memory class for texture
			D3DX_DEFAULT,		// image filter
			D3DX_DEFAULT,		// mip filter
			chromaKey,			// color key for transparency
			&imageInfo,			// file info (from loaded file)
			NULL,				// color palette
			&pTextureOut		// resource pointer destination
		);
	}
	catch (...)
	{
		// throw on error
		throw Error("Error: Failed to load texture from file!");
	}

	// return result status
	return res;
}

// ===========================================================================
// queues a sprite to be drawn with the texture and transforms specified
// by a spriteData struct. should only be called between a
// beginSpriteDraw()...endSpriteDraw() method pair.
// ===========================================================================
void GraphicsHandler::drawSprite(
	const SpriteData&	spriteData,
	COLOR_ARGB			color
) {
	// ensure spriteData contains a valid texture resource, else exit early
	if (spriteData.pTexture == nullptr) return;

	// calculate center of sprite (assuming top-left corner sprite origin)
	D3DXVECTOR3 center {
		(spriteData.width  >> 1) * spriteData.scale,
		(spriteData.height >> 1) * spriteData.scale,
		0.0f
	};

	// define translation transform (translates from world origin {0, 0, 0})
	D3DXVECTOR3 translateVec {
		spriteData.x,
		spriteData.y,
		spriteData.z
	};

	// define scaling transform
	D3DXVECTOR3 scalingVec {
		spriteData.scale,
		spriteData.scale,
		1.0f
	};

	// handle sprite reflection on y-axis (horizontal mirroring)
	if (spriteData.flipY)
	{
		// ====================================================
		// apply the general reflection matrix about the y-axis
		// Ty = [-1  0]
		//      [ 0  1]
		// ====================================================
		scalingVec.x *= -1.0f;

		// update center for reflected sprite
		center.x -= spriteData.width * spriteData.scale;

		// compensate for offset center by translating sprite rightwards 
		// (which is only applied after all other transforms)
		translateVec.x += spriteData.width * spriteData.scale;
	}

	// handle sprite reflection on x-axis (vertical mirroring)
	if (spriteData.flipX)
	{
		// ====================================================
		// apply the general reflection matrix about the y-axis
		// Ty = [1   0]
		//      [0  -1]
		// ====================================================
		scalingVec.y *= -1.0f;

		// update center for reflected sprite
		center.y -= spriteData.height * spriteData.scale;

		// compensate for offset center by translating sprite rightwards 
		// (which is only applied after all other transforms)
		translateVec.y += spriteData.height * spriteData.scale;
	}

	// build rotation quaternion
	D3DXQUATERNION rotationQuad;

	// define rotation matrix
	D3DXMATRIX rotationMatrix;

	// apply z-axis rotation in radians
	D3DXMatrixRotationZ(&rotationMatrix, spriteData.angle);

	// transform rotationMatrix to rotationQuad
	D3DXQuaternionRotationMatrix(&rotationQuad, &rotationMatrix);

	// create final transform matrice
	D3DXMATRIX T;

	// consolidate all transforms into T: R^3 -> R^3
	D3DXMatrixTransformation(
		&T,				// transformation matrix out
		NULL,			// keep origin at top left when scaling
		NULL,			// no scaling rotation
		&scalingVec,	// scale amount
		&center,		// rotation center
		&rotationQuad,	// rotation angle
		&translateVec	// x,y,z position
	);

	// apply T to sprite
	sprite3d->SetTransform(&T);

	// draw sprite at transformed coordinates
	sprite3d->Draw(
		spriteData.pTexture,
		&spriteData.srcRect,
		NULL,
		NULL,
		color
	);
}


// primitive drawing methods

// ===========================================================================
// re-initializes the vertex buffer to a different size, freeing the 
// previous vertex buffer from memory. (default size = 128 vertices)
// ===========================================================================
void GraphicsHandler::resizeVB(
	size_t	maxVertices
) {
	// release previous vertex buffer
	releaseVB();

	// re-initialize vertex buffer to new size
	initializeVB(maxVertices);
}

// ===========================================================================
// draws a set of vertices as the specified primitiveType. the number of 
// vertices should not exceed the maximum number of vertices that can
// be stored within the currently allocated vertex buffer.
// ===========================================================================
void GraphicsHandler::drawVertices(
	Vertex				vertices[],
	size_t				nVertices,
	D3DPRIMITIVETYPE	primitiveType,
	size_t				nPrimitives
) {
	// ensure all vertices can fit into the vertex buffer, else throw warning
	if (nVertices > vbMaxVertices) throw Error(
		"Warning: Drawn vertices exceed vertex buffer size",
		ErrorType::WARNING
	);

	// define pointer to locked memory location
	void* pLockedMem;

	// lock entire vertex buffer to allow write access, clearing all previous 
	// vertices in the process.
	pVB->Lock(0, 0, reinterpret_cast<void**>(&pLockedMem), D3DLOCK_DISCARD);

	// write vertices into locked memory
	memcpy(pLockedMem, vertices, nVertices * sizeof(Vertex));

	// unlock vertex buffer to allow graphics device read access
	pVB->Unlock();

	// queue primitive for drawing
	device3d->DrawPrimitive(primitiveType, 0, nPrimitives);
}

// ===========================================================================
// convenience method - wraps drawVertices() for primitive shape structs
// ===========================================================================
template <size_t nVertices>
void GraphicsHandler::drawPrimitive(
	const PrimitiveShape<nVertices>&	shape
) {
	// delegate work to drawVertices()
	drawVertices(
		shape.vertices,
		nVertices,
		shape.type,
		shape.nPrimitives
	);
}


// message handlers

// ===========================================================================
// handles the window resized notification by updating the presentation
// parameters for the graphics handlers. note that this will reset the 
// directx device in the process.
// ===========================================================================
void GraphicsHandler::handleMessage(
	WindowResized	message,
	MessageBroker*	broker
) {
	// check that the message is from the managed window, else exit early
	if (hWndPtr && message.hwnd != *hWndPtr) return;

	// update the backbuffer width and height accordingly
	bbWidth		= message.newWidth;
	bbHeight	= message.newHeight;

	// reset device to update presentation parameters accordingly
	resetDevice();
}