#include "SolverSupport.h"
#include "arduino.h"

SolverSupport solverSupport = SolverSupport();

// Structs to hold info for support class

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

	clearValueCount();
	clearFilteredValueCount();
	clearCommonLocation();
}
SolverSupport::SolverSupport() {

	clearValueCount();
	clearFilteredValueCount();
	clearCommonLocation();
}

SolverSupport::~SolverSupport() {
	board = nullptr;
}
// Private functions to help with public functions

void SolverSupport::clearValueCount() { 
	// Iterate over array of number counts
	for(uint8_t numberIndex = 0; numberIndex < ELEMENTS; numberIndex++) {
		// Set count to 0
		valueCount[numberIndex].count = 0;
		valueCount[numberIndex].value = 0;

		// Iterate over every location in that particular number count
		for(uint8_t locationIndex = 0; locationIndex < ELEMENTS; locationIndex++) {
			// Set location to number of elements plus 1 (as row/column are 0 index and row/column go from 0 to ELEMENTS - 1)
			valueCount[numberIndex].location[locationIndex].row = ELEMENTS;
			valueCount[numberIndex].location[locationIndex].column = ELEMENTS;
		}
	}
}
void SolverSupport::clearFilteredValueCount() { 
	// Iterate over array of value counts
	for(uint8_t numberIndex = 0; numberIndex < 9; numberIndex++) {
		// Set count and value to 0
		filteredValueCount[numberIndex].count = 0;
		filteredValueCount[numberIndex].value = 0;

		// Iterate over every location in that particular value count
		for(uint8_t locationIndex = 0; locationIndex < 9; locationIndex++) {
			// Set location to number of elements plus 1 (as row/column are 0 index and row/column go from 0 to ELEMENTS - 1)
			filteredValueCount[numberIndex].location[locationIndex].row = ELEMENTS;
			filteredValueCount[numberIndex].location[locationIndex].column = ELEMENTS;
		}
	}
}
void SolverSupport::processPossibleValuesToValueCount(uint8_t row, uint8_t column) {
	// Get all possible values at location
	uint8_t value = 0;
	uint8_t locationIndex = 0;
	board->board[row][column].getPossibleValuesArray(possibleValues);

	//Iterate over every possible value at the selected location
	for(uint8_t i = 0; i < 9; i++) {
		if(possibleValues[i] != 0) {
			// Get possible value and use it to find if it exists yet in the valueCount
			value = possibleValues[i];
			
			// Iterate over value count array
			for(uint8_t j = 0; j < 9; j++) {
				if(valueCount[j].value == value) {
					// Value was found in the array, so add it there
					valueCount[j].count += 1;
					
					// Iterate over locations found so far and find first location
					for(uint8_t k = 0; k < 9; k++) {
						// Find first free spot in location array and add the new location there
						if(valueCount[j].location[k].row == ELEMENTS) {
							valueCount[j].location[k].row = row;
							valueCount[j].location[k].column = column;
						}
					}
					break;
				} else if(valueCount[j].value == 0) {
					// A value of 0 indicates first non-filled entry and thus value was not found.  Add value here
					valueCount[j].value = value;
					valueCount[j].count += 1;
					
					// Add row and column to first entry in location array
					valueCount[j].location[0].row = row;
					valueCount[j].location[0].column = column;
					
					break;
				}
			}
		}
	}
}

// Public functions to help solve sudoku board

void SolverSupport::setBoard(Board *inputBoard) {
	board = inputBoard;
}
void SolverSupport::getValueCountHidden(uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax) {

	// Add all possible values within specifiec rows and columns to number count

	clearValueCount();

	// Iterate over every row and column requested
	for(uint8_t row = rowMin; row <= rowMax; row++) {
		for(uint8_t column = columnMin; column <= columnMax; column++) {
			processPossibleValuesToValueCount(row, column);
		}
	}
}
void SolverSupport::getValueCountNaked(uint8_t possibleValuesMin, uint8_t possibleValuesMax, uint8_t rowMin, uint8_t rowMax,  uint8_t columnMin, uint8_t columnMax) {
	
	// Finds cells within specified rows and columns that have the specified possible values and adds the possible values within that cell.

	clearValueCount();

	// Iterate over every row and column requested
	for(uint8_t row = rowMin; row <= rowMax; row++) {
		for(uint8_t column = columnMin; column <= columnMax; column++) {

			uint8_t numberPossibleValues = board->board[row][column].numberPossibleValues();

			if((numberPossibleValues >= possibleValuesMin) && (numberPossibleValues <= possibleValuesMax)) {
				processPossibleValuesToValueCount(row, column);
			}
		}
	}
}
void SolverSupport::filterValueCount(uint8_t countMin, uint8_t countMax) {

	clearFilteredValueCount();

	uint8_t index = 0;

	for(uint8_t value = 1; value <= 9; value++) {
		if((valueCount[value - 1].count >= countMin) && (valueCount[value - 1].count <= countMax)) {
			filteredValueCount[index].value = value;
			filteredValueCount[index].count = valueCount[value].count;
			for(uint8_t i = 0; i < 9; i++) {
				filteredValueCount[index].location[i] = valueCount[value - 1].location[i];
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
			if(filteredValueCount[value - 1].location[numberLocationIndex].row    == commonLocation[commonIndex].row &&
			   filteredValueCount[value - 1].location[numberLocationIndex].column == commonLocation[commonIndex].column) {
					found = true;
			}
		}
		if(!found) {
			commonLocation[commonLocationIndex].row    = filteredValueCount[value].location[numberLocationIndex].row;
			commonLocation[commonLocationIndex].column = filteredValueCount[value].location[numberLocationIndex].column;
			commonLocationIndex++;
		}
	}
}
void SolverSupport::addCommonLocationValueCount(uint8_t value) {
	bool found = false;
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		if(filteredValueCount[i].value == value) {
			for(uint8_t valueLocationIndex = 0; valueLocationIndex < ELEMENTS; valueLocationIndex++) {
				found = false;
				for(uint8_t commonIndex = 0; commonIndex < ELEMENTS; commonIndex++) {
					if(filteredValueCount[i].location[valueLocationIndex].row    == commonLocation[commonIndex].row &&
					   filteredValueCount[i].location[valueLocationIndex].column == commonLocation[commonIndex].column) {
							found = true;
					}
				}
				if(!found) {
					commonLocation[commonLocationIndex].row    = filteredValueCount[i].location[valueLocationIndex].row;
					commonLocation[commonLocationIndex].column = filteredValueCount[i].location[valueLocationIndex].column;
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

void SolverSupport::displayValueCount() {
	for(int i = 0; i < (int) ELEMENTS; i++) {
		Serial.print("Value: ");
		Serial.println((int) valueCount[i].value);
		Serial.print("Count: ");
		Serial.println((int) valueCount[i].count);
		Serial.println("Locations");
		for(int j = 0; j < (int) ELEMENTS; j++) {
			Serial.print((int) valueCount[i].location[j].row);
			Serial.print(" ");
			Serial.println((int) valueCount[i].location[j].column);
		}
	}
}
void SolverSupport::displayFilteredValueCount() {
	
	
}
void SolverSupport::displayCommonLocations() {
	
	
}

void displayBoard(Board *inputBoard) {
	for(int i = 0; i < (int) ELEMENTS; i++) {
		for(int j = 0; j < (int) ELEMENTS; j++) {
			Serial.print(inputBoard->getValue(i, j));
			Serial.print(" ");
		}
		Serial.println(" ");
	}
}

void waitForInput() {
	bool waiting = true;
	int delayToProcessMultipleCharactersInMSec = 2;
	
	while(waiting){
		if(Serial.available() > 0) {
			while(Serial.available() > 0) {
				Serial.read();
				delay(delayForMultipleCharactersInMSec); 
			}
			waiting = false;
		}
	}
}