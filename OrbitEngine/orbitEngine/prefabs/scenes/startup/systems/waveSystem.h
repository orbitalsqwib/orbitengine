// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Wave System Specification
// ===========================================================================

#ifndef _ORBIT_STARTUP_WAVESYSTEM_H
#define _ORBIT_STARTUP_WAVESYSTEM_H

// import necessary headers
#include "../../../../ecs/ecs.h"
#include "../../../../graphics/components.h"
#include "../components/cellData.h"


// main definition

// renders entities with a sprite data component
class WaveSystem : public System
{
private:

	// members

	// wave constant 
	int waveC;

	// wave width (of continuous colored cells)
	int waveWidth;

	// maximum wave value cap
	int waveMax;

	// wave step offsets - affects time until next wave activates
	int waveOffsets;

	// initial wave step - wave is to maximum left offset
	int initStep;

	// current wave step
	int currStep;

	// maximum wave step - wave is to maximum right offset
	int maxStep;

	// controls speed of wave - delay until wave step is incremented
	float waveStepTime;

	// timer for wave step increments
	float waveTimer;

	// number of waves left to present to user
	int wavesLeft;

	// startup animation color palette
	COLOR_ARGB palette[7];

	// initialization flag
	bool initialized;

public:

	// constructor
	WaveSystem():
		waveC			(0),
		waveWidth		(0),
		waveMax			(6),
		waveOffsets		(0),
		initStep		(0),
		currStep		(0),
		maxStep			(0),
		waveStepTime	(0),
		waveTimer		(0),
		wavesLeft		(0),
		palette			(),
		initialized		(false)
	{}

	// initializer
	void initialize(
		const int&		_waveC,
		const int&		_waveWidth,
		const int&		_waveOffsets,
		const float&	_waveStepTime,
		const int&		_nWaves
	) {
		// update members
		waveC			= _waveC;
		waveWidth		= _waveWidth;
		waveOffsets		= _waveOffsets;
		waveStepTime	= _waveStepTime;
		wavesLeft		= _nWaves;

		// do wave setup calculations
		currStep = initStep = (waveMax + waveC) * -1 - waveOffsets;
		maxStep = initStep * -1 + waveOffsets;

		// define color palette for startup animation
		palette[0] = SETCOLOR_ARGB(255,  34,  17,  80);
		palette[1] = SETCOLOR_ARGB(255,  95,  24, 127);
		palette[2] = SETCOLOR_ARGB(255, 152,  45, 128);
		palette[3] = SETCOLOR_ARGB(255, 211,  67, 110);
		palette[4] = SETCOLOR_ARGB(255, 248, 118,  92);
		palette[5] = SETCOLOR_ARGB(255, 254, 187, 129);
		palette[6] = SETCOLOR_ARGB(255, 252, 253, 191);

		// update flag
		initialized = true;
	}

	// sets the signature for the system
	void setSignature(
		ECSInstance& ecs
	) {
		// set system signature
		Signature s;
		s.set(ecs.getTypeEnum<CellData>(), true);
		s.set(ecs.getTypeEnum<ShapeData>(), true);
		ecs.setSignature<WaveSystem>(s);
	}

	// wave function - maps 2 integers c and r to an integer w
	int w(int c, int r)
	{
		return static_cast<int>(
			waveMax - abs((r + c) / waveWidth - currStep - waveC)
		);
	}

	// update method
	void update(const float& deltaTime)
	{
		// check if system has been initialized, else return early
		if (!initialized) return;

		// increment wave timer
		if (wavesLeft > 0) waveTimer += deltaTime;

		// if timer passes step time, increment wave step
		if (waveTimer >= waveStepTime) {

			// increment wave step
			if (currStep < maxStep) currStep++;
			else
			{
				// reset wave
				currStep = initStep;
				wavesLeft--;
			}

			// reset timer
			waveTimer = 0;
		}

		// update cell entity shape bgs

		// loop through all system entities
		ENTITY_SET::iterator it;
		for (it = entities.begin(); it != entities.end(); it++)
		{
			// get cell data for entity
			CellData* pC = ecs->getComponent<CellData>(*it);

			// get shape data for entity
			ShapeData* pS = ecs->getComponent<ShapeData>(*it);

			// ensure both components exist, else skip entity
			if (!pC || !pS) continue;

			// calculate w value for cell
			int wVal = w(pC->col, pC->row);

			// set shape bg for cell to color at wVal in palette, if wVal > 0 
			pS->color = wVal > 0 ? palette[wVal] : Colors::BLACK;
		}
	}
};

#endif // !_ORBIT_PREFABS_SPRITERENDERSYSTEM_H