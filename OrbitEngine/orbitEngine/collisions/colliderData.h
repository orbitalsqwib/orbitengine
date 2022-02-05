// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Shape Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_COLLISIONS_COLLIDERDATA_H
#define _ORBIT_COLLISIONS_COLLIDERDATA_H

// import minimal windows headers
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

// import necessary headers
#include "dxvec2.h"
#include "../utils/floatRect.h"
#include <assert.h>
#include <string>

// related constructs

enum class ColliderType { NONE, CIRCLE, BOX };
enum class Edge { LEFT, TOP, RIGHT, BOTTOM };


// main definition

struct ColliderData
{
private:

	// give privileged access to collider operator for convenience
	friend class ColliderOperator;

	// members
	ColliderType type;	// specifies the shape of the collider
	std::string tag;	// specifies the collider tag
	Vec2 pos;			// specifies the position of the top-left corner
	float angle;		// specifies the CW rotation (in radians)
	float scale;		// specifies the scale of the collider
	bool ptsDirty;		// specifies if center/corners need recalculation.
	bool boxDirty;		// specifies if rotated box states need recalculation.

	// circle collider states
	float radius;		// specifies the radius of the collider circle

	// box/rotated-box collider states
	FloatRect edges;	// specifies the edges of the collider from the center
	
	// cached calculations
	Vec2 center;				// records the actual center of the collider
	Vec2 corners[4];			// records corner-positions for the collider
	Vec2 edge1UV, edge3UV;		// records unit vectors for projection edges
	float edge1Min, edge1Max;	// records min/max scalar projs. for edge 1
	float edge3Min, edge3Max;	// records min/max scalar projs. for edge 3

	
	// private methods

	// updates the radius to the longest edge
	void updateEdgeRadius()
	{
		// calculate longest edge to use for radial checks
		radius = max(
			max(edges.left, edges.right), 
			max(edges.top, edges.bottom)
		);
	}

public:

	// default constructor
	ColliderData():
		type		(ColliderType::NONE),
		tag			(""),
		pos			(0, 0),
		angle		(0),
		scale		(1),
		ptsDirty	(0),
		boxDirty	(0),
		radius		(0),
		edges		(),
		corners		(),
		edge1UV		(0, 0),
		edge3UV		(0, 0),
		edge1Min	(0),
		edge1Max	(0),
		edge3Min	(0),
		edge3Max	(0)
	{}

	// circle collider constructor
	ColliderData(
		const char	 _tag[32],
		const float& _topLeftX,
		const float& _topLeftY,
		const float& _radius
	):
		type		(ColliderType::CIRCLE),
		tag			(_tag),
		pos			(_topLeftX, _topLeftY),
		angle		(0),
		scale		(1),
		ptsDirty	(true),
		boxDirty	(true),
		radius		(_radius),
		edges		(_radius, _radius, _radius, _radius),
		corners		(),
		edge1UV		(0, 0),
		edge3UV		(0, 0),
		edge1Min	(0),
		edge1Max	(0),
		edge3Min	(0),
		edge3Max	(0)
	{}

	// box collider constructor
	ColliderData(
		const char	 _tag[32],
		const float& _topLeftX,
		const float& _topLeftY,
		const float& _leftEdge,
		const float& _topEdge,
		const float& _rightEdge,
		const float& _bottomEdge
	):
		type		(ColliderType::BOX),
		tag			(_tag),
		pos			(_topLeftX, _topLeftY),
		angle		(0),
		scale		(1),
		ptsDirty	(true),
		boxDirty	(true),
		radius		(0),
		edges		(_leftEdge, _topEdge, _rightEdge, _bottomEdge),
		corners		(),
		edge1UV		(0, 0),
		edge3UV		(0, 0),
		edge1Min	(0),
		edge1Max	(0),
		edge3Min	(0),
		edge3Max	(0)
	{
		// set radius to longest edge
		updateEdgeRadius();
	}

	// box collider shortform constructor
	ColliderData(
		const char	 _tag[32],
		const float& _topLeftX,
		const float& _topLeftY,
		const float& _width,
		const float& _height
	):
		type		(ColliderType::BOX),
		tag			(_tag),
		pos			(_topLeftX, _topLeftY),
		angle		(0),
		scale		(1),
		ptsDirty	(true),
		boxDirty	(true),
		radius		(0),
		edges		(),
		corners		(),
		edge1UV		(0, 0),
		edge3UV		(0, 0),
		edge1Min	(0),
		edge1Max	(0),
		edge3Min	(0),
		edge3Max	(0)
	{
		// set edges
		float xEdge = _width / 2;
		float yEdge = _height / 2;
		edges.left = edges.right = xEdge;
		edges.top = edges.bottom = yEdge;

		// calculate longest edge to use for radial checks
		radius = max(xEdge, yEdge);
	}

	// getters

	// returns the collider type
	ColliderType getType() const { return type; }

	// returns the collider's tag
	std::string getTag() const { return tag; }

	// returns the position of the collider's top-left corner
	const Vec2& getPos() const { return pos; }

	// returns the position of the collider's center
	const Vec2& getCenter() const { return center; }

	// returns the rotation of the collider
	const float& getRotation() const { return angle; }

	// returns the scale of the collider
	const float& getScale() const { return scale; }

	// returns the state of the collider's center/corner states
	bool isPtsDirty() const { return ptsDirty; }

	// returns the state of the collider's rotated box states
	bool isBoxDirty() const { return boxDirty; }

	// returns the radius of the collider
	const float& getRadius() const { return radius; }

	// returns the edges of the collider
	const FloatRect& getEdges() const
	{
		// assert that this method should only be used on box colliders
		assert(type == ColliderType::BOX);

		// return edges struct
		return edges;
	}

	// returns the position for a specific corner of the collider
	const Vec2& getCorner(int n) const
	{
		// assert that this method should only be used on box colliders
		assert(type == ColliderType::BOX);

		// assert that n is in the range (0 <= n < 4)
		assert(n >= 0 && n < 4);

		// return corner
		return corners[n];
	}


	// setters

	// sets the collider's tag
	void setTag(const char _tag[32]) { tag = _tag; }

	// sets the position of the collider (top-left corner)
	void setPos(const float& _x, const float& _y)
	{
		// update position
		pos.x = _x;
		pos.y = _y;

		// mark collider as dirty (needs recalculations)
		ptsDirty = boxDirty = true;
	}

	// sets the rotation of the collider in radians
	void setRotation(const float& _radians)
	{
		// update rotation
		angle = _radians;

		// mark collider as dirty (needs recalculations)
		ptsDirty = boxDirty = true;
	}

	// sets the scale of the collider
	void setScale(const float& _scale)
	{
		// update scale
		scale = _scale;

		// mark collider as dirty (needs recalculations)
		ptsDirty = boxDirty = true;
	}

	// sets the radius of the collider
	void setRadius(const float& _radius)
	{
		// update radius
		radius = _radius;

		// update edges
		edges.left = edges.top = edges.right = edges.bottom = _radius;

		// mark collider as dirty (needs recalculations)
		ptsDirty = boxDirty = true;
	}

	// sets the left edge of the collider
	void setEdge(const Edge& _edge, const float& _length)
	{
		// assert that this method should only be used on box colliders
		assert(type == ColliderType::BOX);

		// update edge
		switch (_edge)
		{
		case Edge::LEFT: edges.left = _length; break;
		case Edge::TOP: edges.top = _length; break;
		case Edge::RIGHT: edges.right = _length; break;
		case Edge::BOTTOM: edges.bottom = _length; break;
		}

		// update radius to longest edge
		updateEdgeRadius();

		// mark collider as dirty (needs recalculations)
		ptsDirty = boxDirty = true;
	}

};

#endif // !_ORBIT_COLLISIONS_COLLIDERDATA_H