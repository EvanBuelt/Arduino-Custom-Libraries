#ifndef SOLVER_SUPPORT_H_
#define SOLVER_SUPPORT_H_

#include <stdint.h>
#include "Board.h"

struct Location {
	uint8_t row;
	uint8_t column;
};

// Stores data about where a particular value is located
struct ValueLocationCount {
	ValueLocationCount();

	Location location[ELEMENTS];
	uint8_t value;
	uint8_t count;
};

class SolverSupport {
private:
	Board *board;

	void clearValueCount();
	void clearFilteredValueCount();
	void processPossibleValuesToValueCount(uint8_t row, uint8_t column);

public:

	SolverSupport(Board *);
	SolverSupport();
	~SolverSupport();

	Location commonLocation[ELEMENTS];
	uint8_t commonLocationIndex;
	ValueLocationCount valueCount[ELEMENTS]; 
	ValueLocationCount filteredValueCount[ELEMENTS]; 
	uint8_t possibleValues[ELEMENTS];	

	void setBoard(Board *);
	void getValueCountHidden(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void getValueCountNaked(uint8_t possibleValuesMin, uint8_t possibleValuesMax, uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void filterValueCount(uint8_t countMin, uint8_t countMax);

	void addCommonLocationNumberCount(uint8_t value);
	void addCommonLocationValueCount(uint8_t value);
	void clearCommonLocation();
	
	void displayValueCount();
	void displayFilteredValueCount();
	void displayCommonLocations();
};

void displayBoard(Board *);
void waitForInput();

/*
Variables used throughout program and defined in SolverSupport.cpp:
Sudoku Support: support class for finding hidden/naked singles/doubles/triples/quads
*/
extern SolverSupport solverSupport;

#endif