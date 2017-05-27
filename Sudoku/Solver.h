#ifndef SOLVER_H_
#define SOLVER_H_

#include <stdint.h>
#include "Board.h"

#include "SolverSupport.h"

/*
Finding hidden process:
-Get NumberLocationCount - Location and count of all possible values in the cells being processed
-Get ValueLocationCount - Location of values within the specified number of counts (2 for doubles, 2-3 for triples, 2-4 for quads)
-Remove hidden doubles/triples/quads - Removes possible values if two/three/four numbers are in the same two/three/four cells only

Finding naked process:
-Find cells with 2/2-3/2-4 possible values based on doubles/triples/quads
-Remove possible values if two/three/four possible values are same in two/three/four cells' possible values
*/

class ElegantSolver {
private:
	Board *board;

	Location commonLocation[ELEMENTS];
	NumberLocationCount numberCount[ELEMENTS]; // When proccessing Hidden values, there are only 9 Cells and 9 Values to process at a time.  
	ValueLocationCount valueCount[ELEMENTS]; 
	uint8_t possibleValues[ELEMENTS];

	// Functions to remove possible values if four values are found
	bool removeNakedQuads();
	bool removeHiddenQuads();

	// Specialty Functions
	bool xWing();
	bool swordfish();

	// Sub functions for triples 
	bool removeNakedQuadRow();
	bool removeNakedQuadColumn();
	bool removeNakedQuadBox();

	bool removeHiddenQuadRow();
	bool removeHiddenQuadColumn();
	bool removeHiddenQuadBox();

	// Utility Functions for hidden x
	bool processHiddenDoubles();
	bool processPointingDoubles();
	bool processHiddenTriples();
	bool processPointingTriples();
	bool processHiddenQuads();

	bool removeValuesInList(uint8_t valueList[WIDTH], uint8_t valueListLength, Location location);
	bool removeValuesNotInList(uint8_t valueList[WIDTH], uint8_t valueListLength, Location location);

	// Uitility Functions for pointing x
	void LocationsInsideArea(Location location[WIDTH], uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void LocationsNotInsideArea(Location location[WIDTH], uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);

	// Uitility Functions for naked x
	void processNakedTriples(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void processNakedQuads(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);

public:

	ElegantSolver(Board *board);

	void solve();
};

#endif