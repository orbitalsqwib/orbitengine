// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : D3DX9 Vector Math Wrappers
// ===========================================================================

#ifndef _ORBIT_COLLIDERS_DXVEC2_H
#define _ORBIT_COLLIDERS_DXVEC2_H

// import necessary headers
#include "../graphics/dximport.h"

// d3dx9 vector aliases
#define Vec2 D3DXVECTOR2

// d3dx9 vector methods
struct Vec2Math
{
	static float length(const Vec2* pVec) 
	{ return D3DXVec2Length(pVec); }

	static float dot(const Vec2* pV1, const Vec2* pV2)
	{ return D3DXVec2Dot(pV1, pV2); }

	static Vec2& normalize(Vec2* pVec)
	{ D3DXVec2Normalize(pVec, pVec); return *pVec; }
};

#endif // !_ORBIT_COLLIDERS_DXVEC2_H