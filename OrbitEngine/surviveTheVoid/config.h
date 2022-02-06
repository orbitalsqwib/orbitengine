// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// SurviveTheVoid : Config Namespaces
// ===========================================================================

#ifndef _STV_CONFIG_H
#define _STV_CONFIG_H

// main definition

// game constants
namespace Config
{
	// horizontal border padding from edge of screen
	const float xBorderPadding = 32;

	// vertical border padding from edge of screen
	const float yBorderPadding = 32;

	// protected radius for enemy spawning
	const float SPAWN_PROTECT_RADIUS = 128;

	// enemy spawn cooldown
	const float ENEMY_SPAWN_COOLDOWN = 1.0f;

	// pickup spawn cooldown
	const float PICKUP_SPAWN_COOLDOWN = 10.0f;

	// pickup blast radius
	const float PICKUP_BLAST_RADIUS = 128;

	// pickup blast duration
	const float PICKUP_BLAST_DURATION = 1.0f;

	// player turn speed (deg/s)
	const float PLAYER_TURN_SPEED = 135;

	// invincibility frame duration
	const float PLAYER_IFRAME_DURATION = 1.5f;
}

#endif // !_STV_CONFIG_H