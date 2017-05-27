#include "SolverSupport.h"

SolverSupport solverSupport = SolverSupport();

// Structs to hold info for support class

NumberLocationCount::NumberLocationCount() {
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		location[i].row = 0;
		location[i].column = 0;
	}
	count = 0;
}
ValueLocationCount::ValueLocationCount() {
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		location[i].row = 0;
		location[i].column = 0;
	}
	value = 0;
	count = 0;
}

// Constructor

SolverSupport::SolverSupport(Board *inputBoard) {
	board = inputBoard;

	clearNumberCount();
	clearValueCount();
	clearCommonLocation();
}
SolverSupport::SolverSupport() {

	clearNumberCount();
	clearValueCount();
	clearCommonLocation();
}

SolverSupport::~SolverSupport() {
	board = nullptr;
}
// Private functions to help with public functions

void SolverSupport::clearNumberCount() { 
	// Iterate over array of number counts
	for(uint8_t numberIndex = 0; numberIndex < ELEMENTS; numberIndex++) {
		// Set count to 0
		numberCount[numberIndex].count = 0;

		// Iterate over every location in that particular number count
		for(uint8_t locationIndex = 0; locationIndex < ELEMENTS; locationIndex++) {
			numberCount[numberIndex].location[locationIndex].row = 0;
			numberCount[numberIndex].location[locationIndex].column = 0;
		}
	}
}
void SolverSupport::clearValueCount() { 
	// Iterate over array of value counts
	for(uint8_t numberIndex = 0; numberIndex < 9; numberIndex++) {
		// Set count and value to 0
		valueCount[numberIndex].count = 0;
		valueCount[numberIndex].value = 0;

		// Iterate over every location in that particular value count
		for(uint8_t locationIndex = 0; locationIndex < 9; locationIndex++) {
			valueCount[numberIndex].location[locationIndex].row = 0;
			valueCount[numberIndex].location[locationIndex].column = 0;
		}
	}
}
void SolverSupport::processPossibleValuesToNumberCount(uint8_t row, uint8_t column) {
	// Get all possible values at location
	uint8_t value = 0;
	uint8_t locationIndex = 0;
	board->board[row][column].getPossibleValuesArray(possibleValues);

	//Iterate over every possible value at the selected location
	for(uint8_t i = 0; i < 9; i++) {
		if(possibleValues[i] != 0) {
			value = possibleValues[i];
			locationIndex = numberCount[value - 1].count;
			numberCount[value - 1].count += 1;
			numberCount[value - 1].location[locationIndex].row = row;
			numberCount[value - 1].location[locationIndex].column = column;
		}
	}
}

// Public functions to help solve sudoku board

void SolverSupport::setBoard(Board *inputBoard) {
	board = inputBoard;
}
void SolverSupport::getNumberCountHidden(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax) {

	// Add all possible values within specifiec rows and columns to number count

	clearNumberCount();

	// Iterate over every row and column requested
	for(uint8_t row = rowMin; row <= rowMax; row++) {
		for(uint8_t column = columnMin; column <= columnMax; column++) {
			processPossibleValuesToNumberCount(row, column);
		}
	}
}
void SolverSupport::getNumberCountNaked(uint8_t possibleValuesMin, uint8_t possibleValuesMax, uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax) {
	
	// Finds cells within specified rows and columns that have the specified possible values and adds the possible values within that cell.

	clearNumberCount();

	// Iterate over every row and column requested
	for(uint8_t row = rowMin; row <= rowMax; row++) {
		for(uint8_t column = columnMin; column <= columnMax; column++) {

			uint8_t numberPossibleValues = board->board[row][column].numberPossibleValues();

			if((numberPossibleValues >= possibleValuesMin) && (numberPossibleValues <= possibleValuesMax)) {
				processPossibleValuesToNumberCount(row, column);
			}
		}
	}
}
void SolverSupport::processNumberCountIntoValueCount(uint8_t countMin, uint8_t countMax) {

	clearValueCount();

	uint8_t index = 0;

	for(uint8_t value = 1; value <= 9; value++) {
		if((numberCount[value - 1].count >= countMin) && (numberCount[value - 1].count <= countMax)) {
			valueCount[index].value = value;
			valueCount[index].count = numberCount[value].count;
			for(uint8_t i = 0; i < 9; i++) {
				valueCount[index].location[i] = numberCount[value - 1].location[i];
			}
			index++;
		}
	}
}

void SolverSupport::addCommonLocationNumberCount(uint8_t value) {
	bool found = false;
	for(uint8_t numberLocationIndex = 0; numberLocationIndex < ELEMENTS; numberLocationIndex++) {
		found = false;
		for(uint8_t commonIndex = 0; commonIndex < ELEMENTS; commonIndex++) {
			if(valueCount[value - 1].location[numberLocationIndex].row    == commonLocation[commonIndex].row &&
			   valueCount[value - 1].location[numberLocationIndex].column == commonLocation[commonIndex].column) {
					found = true;
			}
		}
		if(!found) {
			commonLocation[commonLocationIndex].row    = valueCount[value].location[numberLocationIndex].row;
			commonLocation[commonLocationIndex].column = valueCount[value].location[numberLocationIndex].column;
			commonLocationIndex++;
		}
	}
}
void SolverSupport::addCommonLocationValueCount(uint8_t value) {
	bool found = false;
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		if(valueCount[i].value == value) {
			for(uint8_t valueLocationIndex = 0; valueLocationIndex < ELEMENTS; valueLocationIndex++) {
				found = false;
				for(uint8_t commonIndex = 0; commonIndex < ELEMENTS; commonIndex++) {
					if(valueCount[i].location[valueLocationIndex].row    == commonLocation[commonIndex].row &&
					   valueCount[i].location[valueLocationIndex].column == commonLocation[commonIndex].column) {
							found = true;
					}
				}
				if(!found) {
					commonLocation[commonLocationIndex].row    = valueCount[i].location[valueLocationIndex].row;
					commonLocation[commonLocationIndex].column = valueCount[i].location[valueLocationIndex].column;
					commonLocationIndex++;
				}
			}
		}
	}
}
void SolverSupport::clearCommonLocation() {
	commonLocationIndex = 0;
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		commonLocation[i].row = 0;
		commonLocation[i].column = 0;
	}
}