// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Module:			Gameplay Programming
// Assignment2:		Survive The Void
// Student Name:	Eugene Long
// Student No.:		S10193060J
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// ===========================================================================
// OrbitEngine : Cell Data Struct Specification
// ===========================================================================

#ifndef _ORBIT_STARTUP_CELLDATA_H
#define _ORBIT_STARTUP_CELLDATA_H


// main definition

// defines a cell on the startup screen
struct CellData
{
	// members
	int col;
	int row;

	// convenience constructor
	CellData(
		const int&	_col	= 0,
		const int&	_row	= 0
	):
		col	(_col),
		row	(_row)
	{}
};


#endif // !_ORBIT_STARTUP_CELLDATA_H