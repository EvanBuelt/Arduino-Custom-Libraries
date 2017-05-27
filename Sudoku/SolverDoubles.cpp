#include <stdint.h>
#include "SolverSupport.h"
#include "SolverDoubles.h"
#include "Board.h"

bool removeNakedDoubles(Board &board) {
	bool removed = false;
	removed |= removeNakedDoubleRow(board);
	removed |= removeNakedDoubleColumn(board);
	removed |= removeNakedDoubleBox(board);

	return removed;
}
bool removeHiddenDoubles(Board &board) {
	bool removed = false;

	removed |= removeHiddenDoubleRow(board);
	removed |= removeHiddenDoubleColumn(board);
	removed |= removeHiddenDoubleBox(board);

	return removed;
}
bool removePointingDoubles(Board &board) {
	bool removed = false;

	removed |= removePointingDoubleRow(board);
	removed |= removePointingDoubleColumn(board);
	removed |= removePointingDoubleBox(board);

	return removed;
}

bool removeNakedDoubleRow(Board &board) {
	bool removed = false;

	for(uint8_t row = 0; row < 9; row++) {
		solverSupport.getNumberCountNaked(2, 2, row, row, 0, 8);
		solverSupport.processNumberCountIntoValueCount(2, 9);
		processHiddenDouble(board);
	}
	return removed;
}
bool removeNakedDoubleColumn(Board &board) {
	bool removed = false;

	for(uint8_t column = 0; column < 9; column++) {
		solverSupport.getNumberCountNaked(2, 2, 0, 8, column, column);
		solverSupport.processNumberCountIntoValueCount(2, 9);
		processHiddenDouble(board);
	}
	return removed;
}
bool removeNakedDoubleBox(Board &board) {
	bool removed = false;

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

			solverSupport.getNumberCountNaked(2, 2, rowMin, rowMax, columnMin, columnMax);
			solverSupport.processNumberCountIntoValueCount(2, 9);
			processHiddenDouble(board);
		}
	}
	return removed;
}

bool removeHiddenDoubleRow(Board &board) {
	bool removed = false;

	for(uint8_t row = 0; row < 9; row++) {
		solverSupport.getNumberCountHidden(row, row, 0, 8);
		solverSupport.processNumberCountIntoValueCount(2, 2);
		processHiddenDouble(board);
	}
	return removed;
}
bool removeHiddenDoubleColumn(Board &board) {
	bool removed = false;

	for(uint8_t column = 0; column < 9; column++) {
		solverSupport.getNumberCountHidden(0, 8, column, column);
		solverSupport.processNumberCountIntoValueCount(2, 2);
		processHiddenDouble(board);
	}
	return removed;
}
bool removeHiddenDoubleBox(Board &board) {
	bool removed = false;

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
			solverSupport.processNumberCountIntoValueCount(2, 2);
			processHiddenDouble(board);
		}
	}
	return removed;
}

bool removePointingDoubleRow(Board &board) {
	return false;
}
bool removePointingDoubleColumn(Board &board) {
	return false;
}
bool removePointingDoubleBox(Board &board) {
	return false;
}

bool processHiddenDouble(Board &board) {

	bool found = false;

	for(uint8_t value_1 = 1; value_1 <= 9; value_1++) {
		for(uint8_t value_2 = value_1 + 1; value_2 <= 9; value_2++) {

			solverSupport.clearCommonLocation();
			solverSupport.addCommonLocationValueCount(value_1);
			solverSupport.addCommonLocationValueCount(value_2);

			uint8_t row_1 = solverSupport.commonLocation[0].row;
			uint8_t column_1 = solverSupport.commonLocation[0].column;
			uint8_t row_2 = solverSupport.commonLocation[1].row;
			uint8_t column_2 = solverSupport.commonLocation[1].column;

			if(solverSupport.commonLocationIndex == 2) {
				board.remove_possible_values(row_1, column_1);
				board.remove_possible_values(row_2, column_2);

				board.set_possible_values(value_1, row_1, column_1);
				board.set_possible_values(value_1, row_2, column_2);
				board.set_possible_values(value_2, row_1, column_1);
				board.set_possible_values(value_2, row_2, column_2);
			}
		}
	}
	/*
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
	*/
	return found;
}

/*
bool ElegantSolver::processHiddenDoubles() {
	bool found = false;

	uint8_t count_1 = 0;
	uint8_t count_2 = 0;
	uint8_t row = 0;
	uint8_t column = 0;
	
	for(uint8_t value_1 = 1; value_1 <= 9; value_1++) {
		for(uint8_t value_2 = value_1 + 1; value_2 <= 9; value_2++) {

			// uniqueLocationsInValue(value_1, value_2, 0, 0);
			uint8_t length = 0;
			for(uint8_t i = 0; i < 9; i++) {
				if(commonLocation[i].row == 9) {
					length = i;
					break;
				}
			}

			if(length == 2) {

			}
		}
		/*count = numberCount[value - 1].count;
		if(count == 1) {
			row = numberCount[value - 1].location[0].row;
			column = numberCount[value - 1].location[0].column;

			board.setValue(value, row, column);
			found = true;
		}
	}
	return found;
}*/