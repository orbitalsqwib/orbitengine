// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Collider Operator Class Specification
// ===========================================================================

#ifndef _ORBIT_COLLISIONS_COLLIDEROPERATOR_H
#define _ORBIT_COLLISIONS_COLLIDEROPERATOR_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "colliderData.h"
#include "dxvec2.h"
#include "../common/zvalues.h"
#include "../graphics/graphicsContext.h"


// main definition

class ColliderOperator
{
private:

	// members

	// graphics context for debug rendering
	GraphicsContext* pGraphics;


	// private methods

	// performs center and corner computations for collider states (if dirty)
	void updatePoints(ColliderData& c);

	// performs all pre-computations for collider states (if dirty)
	void update(ColliderData& c);

	// check if projections overlap against another entity
	bool projectionsOverlap(ColliderData& c1, ColliderData& c2);

	// performs collision calculations between two circle colliders.
	bool collideCircle(ColliderData& c1, ColliderData& c2, Vec2& cVOut);

	// box collision calculation (axis-aligned bounding box [aabb] method)
	bool collideBox(ColliderData& c1, ColliderData& c2, Vec2& cVOut);

	// rotated box collision calculation (separating axis test [sat] method)
	bool collideRotatedBox(ColliderData& c1, ColliderData& c2, Vec2& cVOut);

	// rotated box and circle collision calculation (sat method)
	bool collideRBoxCircle(ColliderData& c1, ColliderData& circle, Vec2& cVOut);

	// calc. (circle-corner) voronoi region collisions using a distance check 
	bool collideCornerCircle(Vec2& corner, ColliderData& circle, Vec2& cVOut);

public:

	// constructor
	ColliderOperator() : pGraphics(nullptr) {}

	// initializer

	// binds a graphics context - must be called before using renderDebug()
	void initializeDebug(GraphicsContext* _graphics) 
	{ pGraphics = _graphics; }

	// methods

	// calculates the collision between two collider components and outputs
	// the resultant collision vector. returns true if a collision does occur,
	// and false otherwise. NOTE: the cV returned is from c1's perspective!
	bool collide(ColliderData& c1, ColliderData& c2, Vec2& cVOut);

	// check if collider bounds are outside of the specified rectangle
	int outsideRect(ColliderData& c, const RECT& rect);

	// renders the debug rectangle for colliders
	void renderDebug(ColliderData& c, const COLOR_ARGB& col);
};

#endif // !_ORBIT_COLLISIONS_COLLIDEROPERATOR_H