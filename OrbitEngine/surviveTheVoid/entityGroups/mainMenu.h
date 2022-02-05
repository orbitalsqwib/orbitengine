// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Main Menu Entity Group Specification
// ===========================================================================

#ifndef _STV_ENTITYGROUPS_MAINMENU_H
#define _STV_ENTITYGROUPS_MAINMENU_H

// import necessary headers
#include "../../orbitEngine/imports/ecs.h"
#include "../../orbitEngine/imports/graphics.h"
#include <string>

// local constants
namespace
{
	const std::string TEXTSTYLE_TITLE		= "MAINMENU_TITLE";
	const std::string TEXTSTYLE_OPTION		= "MAINMENU_OPTION";
	const std::string TEXTSTYLE_HIGHLIGHT	= "MAINMENU_HIGHLIGHT";
}


// main definition

// defines and manages a collection of entities that make up the main menu.
class MainMenu
{
private:

	// members

	// menu title entity
	Entity title;

	// menu option entities
	std::vector<Entity> options;

	// menu title string
	std::string titleString;

	// menu option strings
	std::vector<std::string> optionStrings;

	// specifies the padding between the title and the top of the window
	float topPadding;

	// specifies the padding between the left of the window and the menu
	float leftPadding;

	// specifies the spacing between the title and options
	float titleSpacing;

	// specifies the spacing between each option
	float optionSpacing;

	// specifies the main menu theme
	bool lightMode;

	// specifies a pointer reference to the scene's ecs
	ECSInstance* ecs;

	// specifies a pointer reference to an external text style manager
	TextStyleManager* pTextStyleMgr;

	// local text style operator
	UniquePtr<TextStyleOperator> pTextStyleOp;

	// records the current selected option
	int selected;

	// records the height of the title
	int titleH;

	// records the visibility of the menu
	bool active;


	// private methods

	// creates the title entity according to the current main menu states
	void createTitle();

public:

	// constructor
	MainMenu();

	// initializer
	void initialize(
		ECSInstance&		_ecs,
		GraphicsContext&	_graphics,
		TextStyleManager&	_textStyleManager,
		const std::string	_titleString,
		const bool&			_lightMode		= false,
		const float&		_leftPadding	= 64,
		const float&		_topPadding		= 64,
		const float&		_titleSpacing	= 48,
		const float&		_optionSpacing	= 32
	);

	
	// methods

	// adds an option to the main menu
	void addOption(const std::string& _optionString);

	// removes the nth option (0-indexed) from the top of the menu
	void removeOption(const size_t& n);

	// toggles the visibility of the menu
	void toggleMenu(const bool& show);


	// setters

	// sets the current selected option
	void setSelected(int n);

	// updates the current selected option to the next option
	void selectNextOption() { setSelected(selected + 1); };

	// updates the current selected option to the previous option
	void selectPrevOption() { setSelected(selected - 1); };

	// updates the title of the menu
	void setTitle(const std::string _newTitle);

	// updates the string for the nth option
	void setOption(
		const std::string	_newOption,
		const size_t&		_n
	);

	
	// getters

	// returns the string for the currently selected menu option
	int getSelected() const { return selected; }

};

#endif // !_STV_ENTITYGROUPS_MAINMENU_H