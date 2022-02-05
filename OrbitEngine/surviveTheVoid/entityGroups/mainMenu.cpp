// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Main Menu Entity Group Implementation
// ===========================================================================

// import specification
#include "mainMenu.h"


// ===========================================================================
// constructor
// ===========================================================================
MainMenu::MainMenu():

	// members
	title			(ECS_INVALID_ENTITY),
	options			(),
	leftPadding		(0),
	topPadding		(0),
	titleSpacing	(0),
	optionSpacing	(0),
	lightMode		(false),
	ecs				(nullptr),
	pTextStyleMgr	(nullptr),
	selected		(0),
	titleH			(0),
	active			(false)
{}

// ===========================================================================
// initializer
// ===========================================================================
void MainMenu::initialize(
	ECSInstance&		_ecs,
	GraphicsContext&	_graphics,
	TextStyleManager&	_textStyleManager,
	const std::string	_titleString,
	const bool&			_lightMode,
	const float&		_leftPadding,
	const float&		_topPadding,
	const float&		_titleSpacing,
	const float&		_optionSpacing
) {
	// bind ecs and text style manager
	ecs = &_ecs;
	pTextStyleMgr = &_textStyleManager;

	// initialize states
	lightMode = _lightMode;
	leftPadding = _leftPadding;
	topPadding = _topPadding;
	titleSpacing = _titleSpacing;
	optionSpacing = _optionSpacing;

	// setup text style operator
	pTextStyleOp = new TextStyleOperator(&_graphics);

	// setup theme
	COLOR_ARGB foreground = lightMode ? Colors::BLACK : Colors::WHITE;
	COLOR_ARGB highlight = lightMode ? Colors::WHITE : Colors::BLACK;
	COLOR_ARGB highlightBG = foreground;

	// register text styles for menu
	pTextStyleMgr->addStyle(TEXTSTYLE_TITLE,
		TextStyleData(L"Terminal", 36, 0, 0, foreground)
	);
	pTextStyleMgr->addStyle(TEXTSTYLE_OPTION,
		TextStyleData(L"OCR A", 18, 0, 0, foreground & Colors::ALPHA75)
	);
	pTextStyleMgr->addStyle(TEXTSTYLE_HIGHLIGHT,
		TextStyleData(
			L"OCR A", 18, 0, 0, highlight & Colors::ALPHA75, highlightBG
		)
	);

	// set title string
	setTitle(_titleString);

	// create title
	createTitle();

	// update visible status
	active = true;
}


// private methods

// ===========================================================================
// creates the title entity according to the current main menu states
// ===========================================================================
void MainMenu::createTitle()
{
	// create title entity
	title = ecs->createEntity();

	// update title height
	titleH = pTextStyleOp->calculateHeight(
		titleString,
		*pTextStyleMgr->getStyle(TEXTSTYLE_TITLE)
	);

	// add text component for title
	ecs->addComponent<TextData>(title,
		TextData(
			titleString,
			leftPadding,
			topPadding,
			ZValues::OVERLAYS,
			pTextStyleMgr->getStyle(TEXTSTYLE_TITLE)
		)
	);
}


// methods

// ===========================================================================
// adds an option to the main menu
// ===========================================================================
void MainMenu::addOption(
	const std::string&	_optionString
) {
	// add new option string to options string vector
	optionStrings.push_back(_optionString);

	// if menu is hidden, skip creating components for option
	if (!active) return;

	// create option entity
	Entity newOption = ecs->createEntity();

	// get y-pos for option
	float y = topPadding 
		+ titleH 
		+ titleSpacing 
		+ (options.size() * optionSpacing);

	// add text component for option
	ecs->addComponent<TextData>(newOption,
		TextData(
			_optionString,
			leftPadding,
			y,
			ZValues::OVERLAYS,
			pTextStyleMgr->getStyle(TEXTSTYLE_OPTION)
		)
	);

	// add new entity to options entity vector
	options.push_back(newOption);

	// if this is the first option, set this to be selected
	if (options.size() == 1) { setSelected(0); }
}

// ===========================================================================
// removes the nth option (0-indexed) from the top of the menu
// ===========================================================================
void MainMenu::removeOption(
	const size_t&	n
) {
	// ensure n is within options range
	if (n < 0 || n >= options.size()) return;

	// delete nth option entity
	ecs->destroyEntity(options[n]);

	// remove nth option entity and string from vectors
	options.erase(options.begin() + n);
	optionStrings.erase(optionStrings.begin() + n);
}

// ===========================================================================
// toggles the visibility of the menu
// ===========================================================================
void MainMenu::toggleMenu(
	const bool&	show
) {
	// do nothing if current state matches incoming state
	if (show == active) return;

	// if showing menu, recreate all entities from destroyed state
	if (show)
	{
		// update visibility state
		active = true;

		// create title from stored title string
		createTitle();

		// cache all option strings
		std::vector<std::string> tempOptStrings(std::move(optionStrings));

		// clear option vectors to prepare for re-generation of options
		options.clear();
		optionStrings.clear();

		// add all options back in from option string cache
		for (size_t i = 0; i < tempOptStrings.size(); i++)
		{
			addOption(tempOptStrings[i]);
		}
	}

	// if hiding menu, simply destroy all entities
	else
	{
		// update visibility state
		active = false;

		// destroy title
		ecs->destroyEntity(title);

		// reset title entity
		title = ECS_INVALID_ENTITY;

		// destroy all option entities
		for (size_t i = 0; i < options.size(); i++)
		{
			ecs->destroyEntity(options[i]);
		}

		// clear option entities
		options.clear();
	}
}


// setters

// ===========================================================================
// sets the current selected option
// ===========================================================================
void MainMenu::setSelected(
	int	n
) {
	// limit n if n is outside of valid option range
	n = n < 0 
		? options.size() - 1
		: n < int(options.size()) 
			? n 
			: 0;

	// update text style for option
	if (TextData* pText = ecs->getComponent<TextData>(options[n]))
	{
		pText->pStyle = pTextStyleMgr->getStyle(TEXTSTYLE_HIGHLIGHT);
	}

	// reset text style for last selected option, if last selected != n
	if (selected != n && selected >= 0 && selected < int(options.size()))
	{
		if (TextData* pText = ecs->getComponent<TextData>(options[selected]))
		{
			pText->pStyle = pTextStyleMgr->getStyle(TEXTSTYLE_OPTION);
		}
	}

	// update selection
	selected = n;
}

// ===========================================================================
// updates the title of the menu
// ===========================================================================
void MainMenu::setTitle(
	const std::string	_newTitle
) {
	// update title string
	titleString = _newTitle;

	// if menu is hidden, skip text data update for title (doesn't exist)
	if (!active) return;

	// attempt to get text data for title
	if (TextData* pTextData = ecs->getComponent<TextData>(title))
	{
		// update text data
		pTextData->text = _newTitle;
	}
}

// ===========================================================================
// updates the string for the nth option
// ===========================================================================
void MainMenu::setOption(
	const std::string	_newOption,
	const size_t&		_n
) {
	// ensure n is within options range
	if (_n < 0 || _n >= optionStrings.size()) return;

	// update option string
	optionStrings[_n] = _newOption;

	// if menu is hidden, skip text data update for option (doesn't exist)
	if (!active) return;

	// attempt to get text data for option
	if (TextData* pTextData = ecs->getComponent<TextData>(options[_n]))
	{
		// update text data
		pTextData->text = _newOption;
	}
}