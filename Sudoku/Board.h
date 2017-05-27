#ifndef HEADER_H_
#define HEADER_H_

#include <stdint.h>

/* 
Variables used throughout program and defined in Board.cpp:
elements: number of values in sudoku.  Will end up equalling width and height (as Sudoku is sqare for this project)
width: width of sudoku board
height: height of sudoku board
*/

const uint8_t ELEMENTS = 9;
const uint8_t WIDTH = ELEMENTS;
const uint8_t HEIGHT = ELEMENTS;

class Cell {
	// Size of data in Cell is 3 Bytes
private:
	bool isValueInRange(uint8_t);

public:
	uint8_t value;
	uint16_t possible_values;

	Cell();
	Cell(uint8_t);

	void setValue(uint8_t);
	uint8_t getValue();

	bool isPossibleValue(uint8_t);
	uint8_t numberPossibleValues();
	void getPossibleValuesArray(uint8_t[ELEMENTS]);
	bool setPossibleValue(uint8_t);
	bool clearPossibleValue(uint8_t);
};

class Board {
	// Size of data in board is approximately (9*9*3)*2 + 1 + 1 = 488 Bytes
private:
	Cell originalBoard[HEIGHT][WIDTH];

public:

	Cell board[HEIGHT][WIDTH];
	uint8_t width;
	uint8_t height;

	Board();
	Board(uint8_t input_board[HEIGHT][WIDTH]);

	void setValue(uint8_t value, uint8_t row, uint8_t column);
	uint8_t getValue(uint8_t row, uint8_t column);

	void remove_possible_values(uint8_t row, uint8_t column);
	void set_possible_values(uint8_t input_value, uint8_t row, uint8_t column);
};

// Utility functions
bool isBoardSolved(Board &board);

bool isBoardValid(Board &board);

bool isColumnValid(Board &board);

bool isRowValid(Board &board);

bool isBoxValid(Board &board);

#endif