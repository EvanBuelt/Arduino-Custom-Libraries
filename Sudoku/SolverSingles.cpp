#include <stdint.h>
#include "SolverSupport.h"
#include "SolverSingles.h"
#include "Board.h"

bool removeNakedSingles(Board &board) {
	uint8_t possibleValues[ELEMENTS];
	bool found = false;
	for(uint8_t row = 0; row < board.width; row++) {
		for(uint8_t column = 0; column < board.height; column++) {
			if(board.board[row][column].numberPossibleValues() == 1) {
				found = true;
				board.board[row][column].getPossibleValuesArray(possibleValues);
				board.setValue(possibleValues[0], row, column);
			}
		}
	}
	return found;
}
bool removeHiddenSingles(Board &board) {
	bool found = false;
	found |= removeHiddenSingleRow(board);
	found |= removeHiddenSingleColumn(board);
	found |= removeHiddenSingleBox(board);

	return found;
}

bool removeHiddenSingleRow(Board &board) {
	bool result = false;

	uint8_t rowMin = 0;
	uint8_t rowMax = 0;
	uint8_t columnMin = 0;
	uint8_t columnMax = 8;

	for(uint8_t row = 0; row < 9; row++) {

		rowMin = row;
		rowMax = row;

		solverSupport.getNumberCountHidden(rowMin, rowMax, columnMin, columnMax);
		result |= processHiddenSingle(board);
	}
	return result;
}
bool removeHiddenSingleColumn(Board &board) {
	bool result = false;

	uint8_t rowMin = 0;
	uint8_t rowMax = 8;
	uint8_t columnMin = 0;
	uint8_t columnMax = 0;

	for(uint8_t column = 0; column < 9; column++) {
		
		columnMin = column;
		columnMax = column;

		solverSupport.getNumberCountHidden(rowMin, rowMax, columnMin, columnMax);
		result |= processHiddenSingle(board);
	}
	return result;
}
bool removeHiddenSingleBox(Board &board) {
	bool result = false;

	uint8_t rowMin = 0;
	uint8_t rowMax = 0;
	uint8_t columnMin = 0;
	uint8_t columnMax = 0;

	for(uint8_t row = 0; row < 3; row++) {
		for(uint8_t column = 0; column < 3; column++) {

			uint8_t rowMin = row * 3;
			uint8_t rowMax = rowMin + 2;
			uint8_t columnMin = column * 3;
			uint8_t columnMax = columnMin + 2;

			solverSupport.getNumberCountHidden(rowMin, rowMax, columnMin, columnMax);
			result |= processHiddenSingle(board);
		}
	}
	return result;
}

bool processHiddenSingle(Board &board) {
	bool found = false;

	uint8_t count = 0;
	uint8_t row = 0;
	uint8_t column = 0;

	for(uint8_t value = 1; value <= 9; value++) {
		count = solverSupport.numberCount[value - 1].count;
		if(count == 1) {
			row = solverSupport.numberCount[value - 1].location[0].row;
			column = solverSupport.numberCount[value - 1].location[0].column;

			board.setValue(value, row, column);
			found = true;
		}
	}
	return found;
}