// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Timer Entity Group Specification
// ===========================================================================

#ifndef _STV_ENTITYGROUPS_TIMER_H
#define _STV_ENTITYGROUPS_TIMER_H

// import necessary headers
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include <string>


// main definition

// defines and manages a timer entity
class Timer
{
private:

	// members

	// timer entity
	Entity timer;

	// current milliseconds value
	float ms;

	// current seconds value
	int seconds;

	// current minutes value
	int minutes;

	// timer x-pos
	float timerX;

	// timer y-pos
	float timerY;

	// pointer reference to scene ecs
	ECSInstance* ecs;

public:

	// constructor
	Timer() :

		// members
		timer	(ECS_INVALID_ENTITY),
		ms		(0),
		seconds	(0),
		minutes	(0),
		timerX	(0),
		timerY	(0),
		ecs		(nullptr)
	{}

	// initializer
	void initialize(
		ECSInstance&		_ecs,
		GraphicsContext&	_graphics,
		TextStyleManager*	_textStyleManager
	) {
		// save states
		ecs = &_ecs;

		// build new text style operator, automatically deallocated
		TextStyleOperator textStyleOp = TextStyleOperator(&_graphics);

		// create and register timer text style
		_textStyleManager->addStyle("TIMER_TIMERTEXT", 
			TextStyleData(
				L"Terminal", 200, 0, 0, Colors::GRAY & Colors::ALPHA25
			)
		);

		// retrieve pointer to timer text style for convenience
		TextStyleData* pTTS = _textStyleManager->getStyle("TIMER_TIMERTEXT");

		// calculate width and height
		int timerW = textStyleOp.calculateWidth("00:00:00", *pTTS);
		int timerH = textStyleOp.calculateHeight("00:00:00", *pTTS);

		// calculate offsets to center timer
		timerX = (float(_graphics.getDisplayWidth()) - timerW) / 2;
		timerY = (float(_graphics.getDisplayHeight()) - timerH) / 2;

		// build timer
		timer = ecs->createEntity();

		// add timer component
		ecs->addComponent<TextData>(timer, 
			TextData(
			"00:00:00",
			timerX,
			timerY,
			ZValues::BACKGROUND,
			_textStyleManager->getStyle("TIMER_TIMERTEXT")
		));
	}

	
	// methods

	// updates timer
	void update(const float& deltaTime)
	{
		// increment ms
		ms += deltaTime;

		// increment seconds
		if (ms > 1)
		{
			// get whole part
			int increment = static_cast<int>(floor(ms));

			// subtract whole part from ms
			ms -= increment;

			// add increment to seconds
			seconds += increment;
		}

		// increment minutes
		if (seconds >= 60)
		{
			// get minutes within seconds
			int increment = static_cast<int>(floor(seconds / 60));

			// subtract increment from seconds
			seconds -= increment * 60;

			// add increment to minutes
			minutes += increment;
		}

		// update text components
		if (TextData* pText = ecs->getComponent<TextData>(timer))
		{
			// update timer text
			pText->text = getTimeStr();
		}
	}

	// resets timer
	void reset()
	{
		seconds = minutes = 0;
		ms = 0;

		// update text components
		if (TextData* pText = ecs->getComponent<TextData>(timer))
		{
			// update timer text
			pText->text = "00:00:00";
		}
	}

	// returns the current time as a formatted string
	std::string getTimeStr()
	{
		// pad leading zeroes for minute string
		std::string minStr = std::to_string(minutes);
		if (minutes < 10) minStr.insert(0, "0");

		// pad leading zeroes for seconds string
		std::string secStr = std::to_string(seconds);
		if (seconds < 10) secStr.insert(0, "0");

		// pad leading zeroes for milliseconds string
		std::string msStr = std::to_string(int(ms * 100));
		if (ms < 0.1) msStr.insert(0, "0");

		// calculate final text
		return minStr + ":" + secStr + ":" + msStr;
	}

};

#endif // !_STV_ENTITYGROUPS_TIMER_H