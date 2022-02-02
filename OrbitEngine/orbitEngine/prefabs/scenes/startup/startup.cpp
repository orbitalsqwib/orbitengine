// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Startup Scene Implementation
// ===========================================================================

// import specification
#include "startup.h"


// scene methods

// ===========================================================================
// scene setup method - should set up all entities, components and systems
// that will be used / displayed within the scene. this method is invoked
// on transitioning to the scene, and is guaranteed to be run before the
// scene update loop is run.
// ===========================================================================
void StartupScene::setup()
{
	// ! setup graphics

	// setup rendering system
	renderSystems.initialize(ecs, &engine->graphics());

	// set background color
	engine->graphics().setBGColor(Colors::BLACK);


	// ! setup basic systems

	// initialize transform listener
	transformListener.initialize(ecs, sceneBroker);


	// ! setup text objects

	// build new text style manager
	pTextStyleManager = new TextStyleManager(&engine->graphics());

	// register text styles
	int textH = 18;
	pTextStyleManager->addStyle("default", 
		TextStyleData(L"OCR A", textH, 0, 0, Colors::BLACK, Colors::WHITE)
	);
	pTextStyleManager->addStyle("light", 
		TextStyleData(L"OCR A", textH, 0, 0, Colors::WHITE & Colors::ALPHA25)
	);


	// ! register components
	ecs.registerComponent<PositionData>();
	ecs.registerComponent<CellData>();


	// ! scene setup

	// specify row and column spacings for grid
	int colSpacing = 7;
	int rowSpacing = 10;

	// initialize text style operator
	TextStyleOperator tsOp(&engine->graphics());

	// calculate title width
	int titleW = tsOp.calculateWidth(
		"orbit:engine",
		*pTextStyleManager->getStyle("default")
	);

	// get window dimensions
	RECT windowRect;
	GetClientRect(engine->graphics().getHwnd(), &windowRect);

	// calculate cell dimensions
	int cellW = titleW + colSpacing;
	int cellH = textH + rowSpacing;

	// get number of title texts required to fill width of screen
	int nTitleCols = windowRect.right / cellW + 2;
	int nTitleRows = windowRect.bottom / cellH + 2;

	// calculate offsets required to center text display vertically
	int xOffset = ((nTitleCols * cellW) - windowRect.right) / 2;

	// choose a random col and row to highlight
	srand(static_cast<unsigned int>(time(NULL)));
	int hlCol = rand() % (nTitleCols - 4) + 2;
	int hlRow = rand() % (nTitleRows - 4) + 2;

	// setup wave system
	int		waveW			= 7;
	int		waveC			= ((nTitleCols + nTitleRows) >> 1) / waveW;
	int		waveOffsets		= 3;
	float	waveStepTime	= 0.025f;
	int		nWaves			= 3;

	pWaveSystem = ecs.registerSystem<WaveSystem>();
	pWaveSystem->initialize(
		waveC,
		waveW,
		waveOffsets,
		waveStepTime,
		nWaves
	);


	// ! do entity setup

	// setup animation entities
	for (int r = 0; r < nTitleRows; r++)
	{
		for (int c = 0; c < nTitleCols; c++)
		{
			// generate new cell entity
			Entity cell = ecs.createEntity();

			// each cell entity should have a text component
			ecs.addComponent<TextData>(
				cell,
				TextData(
					"orbit:engine",
					static_cast<float>(c * cellW - xOffset),
					static_cast<float>(r * cellH),
					ZValues::FOREGROUND,
					r == hlRow && c == hlCol
						? pTextStyleManager->getStyle("default")
						: pTextStyleManager->getStyle("light")
				)
			);

			// each cell entity should also have a rectangle bg
			ecs.addComponent<ShapeData>(
				cell,
				ShapeData(
					BasicShape::RECTANGLE,
					static_cast<float>(c * cellW - xOffset),
					static_cast<float>(r * cellH),
					ZValues::BACKGROUND,
					static_cast<float>(cellW),
					static_cast<float>(cellH)
				)
			);

			// each cell entity should also record their grid position
			ecs.addComponent<CellData>(
				cell,
				CellData(c, r)
			);
		}
	}
}

// ===========================================================================
// scene update method - should specify the order in which systems are run
// as well as handle other game logic that will be run every frame. this
// method is invoked every frame, and constitutes the main update loop for
// a particular scene. this method is guaranteed to not be run when the
// scene is paused or halted, thus all updates within this loop will be
// put in a sort of "stasis" until the scene is resumed.
// ===========================================================================
void StartupScene::update(
	const float&	deltaTime
) {
	pWaveSystem->update(deltaTime);
	renderSystems.render(deltaTime);
}

// ===========================================================================
// scene teardown method - should clean up all non-ecs objects or states
// that the scene introduces over its lifecycle. (ecs-managed objects will
// be handled automatically by the ecs system) this method is only invoked
// when transitioning out of the scene, and will not be called if the
// scene is paused or halted temporarily.
// ===========================================================================
void StartupScene::teardown()
{
	// reset background color
	engine->graphics().setBGColor(Colors::LIME);
}