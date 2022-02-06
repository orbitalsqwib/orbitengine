// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Collider Operator Class Implementation
// ===========================================================================

// import specification
#include "colliderOperator.h"


// private methods

// ===========================================================================
// performs center and corner computations for collider states (if dirty)
// ===========================================================================
void ColliderOperator::updatePoints(
	ColliderData&	c
) {
	// ensure point data for c is dirty before re-computing states
	if (!c.ptsDirty) return;

	switch (c.type)
	{
	case ColliderType::BOX:
	{
		// update center for collider
		c.center.x = c.pos.x + c.edges.left * c.scale;
		c.center.y = c.pos.y + c.edges.top * c.scale;
	}
	case ColliderType::CIRCLE:
	{
		// update center for collider
		c.center.x = c.pos.x + c.radius * c.scale;
		c.center.y = c.pos.y + c.radius * c.scale;
	}
	}

	// corner numbers

	// 0---1
	// |   |
	// 3---2

	// calculate unit vectors for rotated axes
	Vec2 xRotatedUV (
		static_cast<float>(  cos(c.angle)  ), 
		static_cast<float>(  sin(c.angle)  )
	);
	Vec2 yRotatedUV (
		static_cast<float>( -sin(c.angle)  ),
		static_cast<float>(  cos(c.angle)  )
	);

	// update corners
	c.corners[0] = c.center +
		xRotatedUV * (c.edges.left		* c.scale) +
		yRotatedUV * (c.edges.top		* c.scale);
	c.corners[1] = c.center +
		xRotatedUV * (c.edges.right		* c.scale) +
		yRotatedUV * (c.edges.top		* c.scale);
	c.corners[2] = c.center +
		xRotatedUV * (c.edges.right		* c.scale) +
		yRotatedUV * (c.edges.bottom	* c.scale);
	c.corners[3] = c.center +
		xRotatedUV * (c.edges.left		* c.scale) +
		yRotatedUV * (c.edges.bottom	* c.scale);

	// calculations complete, update status
	c.ptsDirty = false;
}

// ===========================================================================
// performs all pre-computations for collider states (if dirty)
// ===========================================================================
void ColliderOperator::update(
	ColliderData&	c
) {
	// ensure box data for c is dirty before re-computing states
	if (!c.boxDirty) return;

	// recalculate collider points if necessary
	updatePoints(c);

	// calculate projection line vectors, using corners[0] as origin
	c.edge1UV = Vec2 (
		c.corners[1].x - c.corners[0].x,
		c.corners[1].y - c.corners[0].y
	);
	c.edge3UV = Vec2 (
		c.corners[3].x - c.corners[0].x,
		c.corners[3].y - c.corners[0].y
	);

	// normalize vectors for each projection line vector to get direction vecs
	Vec2Math::normalize(&c.edge1UV);
	Vec2Math::normalize(&c.edge3UV);

	// get minimum and maximum projection for each edge

	// initialize shared scalar projection container
	float projection;

	// 1. get first scalar projection for edge 1
	projection = Vec2Math::dot(&c.edge1UV, &c.corners[0]);

	// 2. we don't know whether this is the min or the max projection, so 
	// we'll initialize both the min and the max to this projection first
	c.edge1Min = c.edge1Max = projection;

	// 3. get second scalar projection for edge 1
	projection = Vec2Math::dot(&c.edge1UV, &c.corners[1]);

	// 4. now we can check if the new projection is the min or max projection by
	// comparing it with the previous min/max values.
	if		(projection < c.edge1Min) c.edge1Min = projection;
	else if (projection > c.edge1Max) c.edge1Max = projection;

	// repeat steps 1 - 4 for edge 3

	// 1.
	projection = Vec2Math::dot(&c.edge3UV, &c.corners[0]);

	// 2.
	c.edge3Min = c.edge3Max = projection;

	// 3.
	projection = Vec2Math::dot(&c.edge3UV, &c.corners[1]);

	// 4.
	if		(projection < c.edge3Min) c.edge3Min = projection;
	else if (projection > c.edge3Max) c.edge3Max = projection;

	// calculations complete, update status
	c.boxDirty = false;
}

// ===========================================================================
// check if projections overlap against another entity
// ===========================================================================
bool ColliderOperator::projectionsOverlap(
	ColliderData&	c1,
	ColliderData&	c2
) {
	// working state - shared projection scalar container
	float projection;

	// working states - temporary projection states for other collider
	float oEdge1Min, oEdge1Max, oEdge3Min, oEdge3Max;

	// project other box collider onto this collider's edge1 and edge3 axes

	// project corner 0
	projection = Vec2Math::dot(&c1.edge1UV, &c2.corners[0]);
	oEdge1Min = oEdge1Max = projection;

	// for each remaining corner,
	for (int c = 1; c < 4; c++)
	{
		// project the corner onto edge1, update min/max values accordingly
		projection = Vec2Math::dot(&c1.edge1UV, &c2.corners[c]);
		if		(projection < oEdge1Min) oEdge1Min = projection;
		else if (projection > oEdge1Max) oEdge1Max = projection;
	}

	// if projections do not overlap, no collision is possible
	if (oEdge1Min > c1.edge1Max || oEdge1Max < c1.edge1Min) return false;

	// project corner 3
	projection = Vec2Math::dot(&c1.edge3UV, &c2.corners[0]);
	oEdge3Min = oEdge3Max = projection;

	// for each remaining corner,
	for (int c = 1; c < 4; c++)
	{
		// project the corner onto edge1, update min/max values accordingly
		projection = Vec2Math::dot(&c1.edge3UV, &c2.corners[c]);
		if		(projection < oEdge3Min) oEdge3Min = projection;
		else if (projection > oEdge3Max) oEdge3Max = projection;
	}

	// if projections do not overlap, no collision is possible
	if (oEdge3Min > c1.edge3Max || oEdge3Max < c1.edge3Min) return false;

	// else, if both axes projections overlap, collision has occured
	return true;
}

// ===========================================================================
// performs collision calculations between two circle colliders.
// ===========================================================================
bool ColliderOperator::collideCircle(
	ColliderData&	c1,
	ColliderData&	c2,
	Vec2&			cVOut
) {
	// let collider c1's center be OA
	// let collider c2's center be OB

	// update colliders center if necessary
	updatePoints(c1);
	updatePoints(c2);

	// get distance between circle centers
	Vec2 dist2 = c1.center - c2.center;

	// by pythogoreas theorem: distance^2 = a^2 + b^2
	dist2.x = dist2.x * dist2.x;
	dist2.y = dist2.y * dist2.y;

	// calculate sum of radii (adjusted for collider scale)
	float sumRadii2 = (c1.radius * c1.scale) + (c2.radius * c2.scale);

	// square sum of radii to match squared distance
	sumRadii2 *= sumRadii2;

	// if d < (r1 + r2), circles are intersecting -> collision occured
	// d < (r1 + r2)				<=>		sqrt(a^2 + b^2) < (r1 + r2)
	// sqrt(a^2 + b^2) < (r1 + r2)	<=>		(a^2 + b^2) < (r1 + r2)^2

	// if entities are not colliding, return no collision occured
	if (dist2.x + dist2.y > sumRadii2) return false;

	// else calculate collision vector (AB = OB - OA)
	cVOut = c2.center - c1.center;

	// return collision occured
	return true;
}

// ===========================================================================
// box collision calculation (axis-aligned bounding box [aabb] method)
// ===========================================================================
bool ColliderOperator::collideBox(
	ColliderData&	c1,
	ColliderData&	c2,
	Vec2&			cVOut
) {
	// let collider c1's center be OA
	// let collider c2's center be OB

	// update colliders center if necessary
	updatePoints(c1);
	updatePoints(c2);

	// check for collision using axis aligned bounding box check
	if (
		// the right edge is to the left of the other collider's left edge
		(c1.center.x + c1.edges.right * c1.scale < 
		 c2.center.x + c2.edges.left * c2.scale)	||

		// the left edge is to the right of the other collider's right edge
		(c1.center.x + c1.edges.left * c1.scale >
		 c2.center.x + c2.edges.right * c2.scale)	||

		// the bottom edge is above the other collider's top edge
		(c1.center.y + c1.edges.bottom * c1.scale <
		 c2.center.y + c2.edges.top * c2.scale)		||

		// the top edge is below the other collider's bottom edge
		(c1.center.y + c1.edges.top * c1.scale >
		 c2.center.y + c2.edges.bottom * c2.scale)
	)
		// if any of these are true, return no collision occured
		return false;

	// else calculate collision vector (AB = OB - OA)
	cVOut = c2.center - c1.center;

	// return collision occured
	return true;
}

// ===========================================================================
// rotated box collision calculation (separating axis test [sat] method)
// ===========================================================================
bool ColliderOperator::collideRotatedBox(
	ColliderData&	c1,
	ColliderData&	c2,
	Vec2&			cVOut
) {
	// let collider c1's center be OA
	// let collider c2's center be OB

	// prepare rotated box states for both colliders
	update(c1);
	update(c2);

	// check if collider projections fail to overlap
	if (!projectionsOverlap(c1, c2) || !projectionsOverlap(c2, c1))

		// return no collision occurred
		return false;

	// else calculate collision vector (AB = OB - OA)
	cVOut = c2.center - c1.center;

	// return collision occured
	return true;
}

// ===========================================================================
// rotated box and circle collision calculation (sat method)
// ===========================================================================
bool ColliderOperator::collideRBoxCircle(
	ColliderData&	c1,
	ColliderData&	circle,
	Vec2&			cVOut
) {
	// working states - temporary projection states for circle
	float center1, center3, cEdge1Min, cEdge1Max, cEdge3Min, cEdge3Max;

	// prepare rotated box for collider c1
	update(c1);

	// project circle center onto edge 1
	center1	= Vec2Math::dot(&c1.edge1UV, &circle.center);

	// calculate min and max projections for circle on edge 1
	cEdge1Min = center1 - circle.radius * circle.scale;
	cEdge1Max = center1 + circle.radius * circle.scale;

	// if projections do not overlap, no collision is possible
	if (cEdge1Min > c1.edge1Max || cEdge1Max < c1.edge1Min) return false;

	// project circle center onto edge3
	center3 = Vec2Math::dot(&c1.edge3UV, &circle.center);

	// calculate min and max projections for circle on edge 3
	cEdge3Min = center3 - circle.radius * circle.scale;
	cEdge3Max = center3 + circle.radius * circle.scale;

	// if projections do not overlap, no collision is possible
	if (cEdge3Min > c1.edge3Max || cEdge3Max < c1.edge3Min) return false;


	// if circle projection overlaps box projection

	// if the circle center is outside the lines extended from the collision 
	// box edges (voronoi region), then the nearest box corner is checked for
	// collision using a distance check.
	
	//   voronoi0 |   | voronoi1
	//         ---0---1---
	//            |   |
	//         ---3---2---
	//   voronoi3 |   | voronoi2
	
	// use overlap test to determine nearest corner

	// if circle in voronoi0, compute corner checks for corner 0
	if (center1 < c1.edge1Min && center3 < c1.edge3Min)
		return collideCornerCircle(c1.corners[0], circle, cVOut);

	// if circle in voronoi1, compute corner checks for corner 1
	if (center1 > c1.edge1Max && center3 < c1.edge3Min)
		return collideCornerCircle(c1.corners[1], circle, cVOut);

	// if circle in voronoi2, compute corner checks for corner 2
	if (center1 > c1.edge1Max && center3 > c1.edge3Max)
		return collideCornerCircle(c1.corners[2], circle, cVOut);

	// if circle in voronoi3, compute corner checks for corner 3
	if (center1 < c1.edge1Min && center3 > c1.edge3Max)
		return collideCornerCircle(c1.corners[3], circle, cVOut);

	// if no overlaps, circle not in voronoi region, so it is colliding with
	// an edge of the box.

	// calculate collision vector (center of circle -> center of box)
	cVOut = circle.center - c1.center;

	// return collision occursed
	return true;
}

// ===========================================================================
// calc. (circle-corner) voronoi region collisions using a distance check 
// ===========================================================================
bool ColliderOperator::collideCornerCircle(
	Vec2&			corner,
	ColliderData&	circle,
	Vec2&			cVOut
) {
	// let the corner's position vector be OA
	// let circle collider's center be OB
	
	// get distance between corner and circle center
	Vec2 dist2 = corner - circle.center;

	// by pythogoreas theorem: distance^2 = a^2 + b^2
	dist2.x = dist2.x * dist2.x;
	dist2.y = dist2.y * dist2.y;

	// calculate sum of radii (adjusted for collider scale)
	// note that corner has a radii of 0, therefore it is (0 + circle radii)
	float sumRadii2 = (circle.radius * circle.scale);

	// square sum of radii to match squared distance
	sumRadii2 *= sumRadii2;

	// if d < (r1 + r2), circles are intersecting -> collision occured
	// d < (r1 + r2)				<=>		sqrt(a^2 + b^2) < (r1 + r2)
	// sqrt(a^2 + b^2) < (r1 + r2)	<=>		(a^2 + b^2) < (r1 + r2)^2

	// if entities are not colliding, return no collision occured
	if (dist2.x + dist2.y > sumRadii2) return false;

	// else calculate collision vector (AB = OB - OA)
	cVOut = circle.center - corner;

	// return collision occured
	return true;
}


// public methods

// ===========================================================================
// calculates the collision between two collider components and outputs
// the resultant collision vector. returns true if a collision does occur,
// and false otherwise. NOTE: the cV returned is from c1's perspective!
// ===========================================================================
bool ColliderOperator::collide(
	ColliderData&	c1,
	ColliderData&	c2,
	Vec2&			cVOut
) {
	// handle circle-circle collision
	if (
		c1.type == ColliderType::CIRCLE && 
		c2.type == ColliderType::CIRCLE
	) {
		return collideCircle(c1, c2, cVOut);
	}

	// handle simple box-box collision (neither box is rotated)
	if (
		c1.type == ColliderType::BOX && c1.angle == 0 &&
		c2.type == ColliderType::BOX && c2.angle == 0
	) {
		return collideBox(c1, c2, cVOut);
	}

	// all other combinations should use separating axis test

	// handle box-rotatedbox / rotatedbox-box collision (neither is circle)
	if (
		c1.type != ColliderType::CIRCLE &&
		c2.type != ColliderType::CIRCLE
	) {
		return collideRotatedBox(c1, c2, cVOut);
	}

	// handle rest of combinations (one of the colliders is a circle)

	// the other collider is a circle collider
	if (c1.type != ColliderType::CIRCLE)
	{
		return collideRBoxCircle(c1, c2, cVOut);
	}

	// else, this collider is a circle collider, so we check for collision 
	// from the other collider with our circle collider

	// compute collision from other object
	bool collide = collideRBoxCircle(c2, c1, cVOut);

	// reverse other collider's collision vector to get our collision vector
	if (collide) cVOut *= -1;

	// return collision status
	return collide;
}

// ===========================================================================
// check if collider bounds are outside of the specified rectangle
//
// returns an integer corresponding to the side which the collider exceeded,
// else 0 if the collider is inside the rect.
// 
//   __2__
//  |     |
// 1|  0  |3
//  |_____|
//     4
// 
// ===========================================================================
int ColliderOperator::outsideRect(
	ColliderData&	c, 
	const RECT&		rect
) {
	// get updated points
	updatePoints(c);

	// if collider is a circle, check if axis-aligned edge projections of 
	// circle are completely inside of rect edges
	if (c.type == ColliderType::CIRCLE)
	{
		if (c.center.x - c.radius * c.scale < rect.left)	return 1;
		if (c.center.x + c.radius * c.scale > rect.right)	return 3;
		if (c.center.y - c.radius * c.scale < rect.top)		return 2;
		if (c.center.y + c.radius * c.scale > rect.bottom)	return 4;
	}

	// else, check if box corners are outside of rect
	else if (c.type == ColliderType::BOX)
	{
		// check if any corner is completely outside of rect edge projection
		for (int i = 0; i < 4; i++) {

			if (c.corners[i].x < rect.left)		return 1;
			if (c.corners[i].x > rect.right)	return 3;
			if (c.corners[i].y < rect.top)		return 2;
			if (c.corners[i].y > rect.bottom)	return 4;
		}
	}

	// else, collider is inside of the rect
	return 0;
}

// ===========================================================================
// renders the debug rectangle for colliders
// ===========================================================================
void ColliderOperator::renderDebug(
	ColliderData&		c, 
	const COLOR_ARGB&	col
) {
	// only render if graphics context has been initialized
	if (!pGraphics) return;

	// get updated corners
	updatePoints(c);

	// set up vertices for debug outline
	Vertex vertices[5]
	{
		Vertex(
			c.corners[0].x, c.corners[0].y, ZValues::RESERVED, col, 0.0f, 0.0f
		),
		Vertex(
			c.corners[1].x, c.corners[1].y, ZValues::RESERVED, col, 1.0f, 0.0f
		),
		Vertex(
			c.corners[2].x, c.corners[2].y, ZValues::RESERVED, col, 1.0f, 1.0f
		),
		Vertex(
			c.corners[3].x, c.corners[3].y, ZValues::RESERVED, col, 0.0f, 1.0f
		),
		Vertex(
			c.corners[0].x, c.corners[0].y, ZValues::RESERVED, col, 0.0f, 0.0f
		)
	};

	// draw vertices
	if (pGraphics->beginSpriteDraw() == D3D_OK)
	{
		pGraphics->drawVertices(vertices, 5, D3DPT_LINESTRIP, 4);
		pGraphics->endSpriteDraw();
	}
}