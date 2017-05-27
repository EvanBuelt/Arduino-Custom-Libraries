#ifndef SOLVER_SUPPORT_H_
#define SOLVER_SUPPORT_H_

#include <stdint.h>
#include "Board.h"

struct Location {
	uint8_t row;
	uint8_t column;
};
struct NumberLocationCount {
	NumberLocationCount();

	Location location[ELEMENTS];
	uint8_t count;
};
struct ValueLocationCount {
	ValueLocationCount();

	Location location[ELEMENTS];
	uint8_t value;
	uint8_t count;
};

class SolverSupport {
private:
	Board *board;

	void clearNumberCount();
	void clearValueCount();
	void processPossibleValuesToNumberCount(uint8_t row, uint8_t column);

public:

	SolverSupport(Board *);
	SolverSupport();
	~SolverSupport();

	Location commonLocation[ELEMENTS];
	uint8_t commonLocationIndex;
	NumberLocationCount numberCount[ELEMENTS]; 
	ValueLocationCount valueCount[ELEMENTS]; 
	uint8_t possibleValues[ELEMENTS];	

	void setBoard(Board *);
	void getNumberCountHidden(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void getNumberCountNaked(uint8_t possibleValuesMin, uint8_t possibleValuesMax, uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax);
	void processNumberCountIntoValueCount(uint8_t countMin, uint8_t countMax);

	void addCommonLocationNumberCount(uint8_t value);
	void addCommonLocationValueCount(uint8_t value);
	void clearCommonLocation();
};

/*
Variables used throughout program and defined in SolverSupport.cpp:
Sudoku Support: support class for finding hidden/naked singles/doubles/triples/quads
*/
extern SolverSupport solverSupport;

#endif