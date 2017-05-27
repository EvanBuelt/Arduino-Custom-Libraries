#include "Board.h"

// Cell function definitions
Cell::Cell() {
	value = 0;
	possible_values = 0x01FF; // 0000 0001 1111 1111: Bits 0-8 are true, implying 1-9 are possible values
}

Cell::Cell(uint8_t initial_value) {
	if(isValueInRange(initial_value)) {
		value = initial_value;
		possible_values = 0x0000; // 0000 0000 0000 0000: Bits 0-8 are false, implying 1-9 are not possible values
	} else {
		value = 0;
		possible_values = 0x01FF; // 0000 0001 1111 1111: Bits 0-8 are true, implying 1-9 are possible values
	}
}

bool Cell::isValueInRange(uint8_t input_value) {
	return ((input_value >=1) && (input_value <= ELEMENTS));
}

void Cell::setValue(uint8_t new_value) {
	if(new_value == 0){
		value = new_value;
		possible_values = 0x01FF;// 0000 0001 1111 1111: Bits 0-8 are true, implying 1-9 are possible values
	} else if(isValueInRange(new_value)) {
		value = new_value;
		possible_values = 0x0000; // 0000 0000 0000 0000: Bits 0-8 are false, implying 1-9 are not possible values
	}
}

uint8_t Cell::getValue() {
	return value;
}

uint8_t Cell::numberPossibleValues() {
	uint8_t count = 0;
	for(uint8_t i = 0; i < ELEMENTS; i++) {
		if((possible_values >> i) & 0x0001) {
			count++;
		}
	}
	return count;
}
void Cell::getPossibleValuesArray(uint8_t* possibleValuesArray) {
	uint8_t index = 0;
	for(uint8_t value = 1; value <= ELEMENTS; value++) {
		possibleValuesArray[value - 1] = 0;
		if((possible_values >> (value - 1)) & 0x0001) {
			possibleValuesArray[index] = value;
			index++;
		}
	}
}
bool Cell::isPossibleValue(uint8_t input_value) {
	if(isValueInRange(input_value)) {
		return (possible_values >> (input_value - 1)) & 0x0001;
	} else {
		return false;
	}
}
bool Cell::setPossibleValue(uint8_t input_value) {
	bool result = false;
	if(isValueInRange(input_value) && (value == 0)) {
		result = ((possible_values >> (input_value - 1)) & 1) == 0;
		possible_values |= (1 << (input_value - 1));
	}
	return result;
}
bool Cell::clearPossibleValue(uint8_t input_value) {
	bool result = false;
	if(isValueInRange(input_value)) {
		result = ((possible_values >> (input_value - 1)) & 1) > 0;
		possible_values &= ~(1 << (input_value - 1));
	}
	return result;
}

// Board function definitions
Board::Board() {
	// Assume a standard Sudoku of width and height 9
	width = WIDTH;
	height = HEIGHT;

	for(uint8_t column = 0; column < width; column++) {
		for(uint8_t row = 0; row < height; row++) {
			originalBoard[row][column].setValue(0);
			setValue(0, row, column);
		}
	}
}
Board::Board(uint8_t input_board[HEIGHT][WIDTH]) {
	// Assume standard Sudoku board of width 9 and height 9
	width = WIDTH;
	height = HEIGHT;

	for(uint8_t column = 0; column < width; column++) {
		// Initialize values within board board
		for(uint8_t row = 0; row < height; row++) {
			uint8_t value = input_board[row][column];

			// Only set value if a non-zero single digit number
			if((value >= 1) && (value <= 9)){
				originalBoard[row][column].setValue(value);
				setValue(value, row, column);
			}
		}
	}
}

void Board::setValue(uint8_t value, uint8_t row, uint8_t column) {
	if((row >= 0) && (row < height) && (column >= 0) && (column < width)) {
		board[row][column].setValue(value);
		remove_possible_values(row, column);
	}
}
uint8_t Board::getValue(uint8_t row, uint8_t column) {
	if((row >= 0) && (row < height) && (column >= 0) && (column < width)) {
		return board[row][column].getValue();
	} else {
		return 0;
	}
}

void Board::remove_possible_values(uint8_t row, uint8_t column) {

	uint8_t boxRowStart = 3 * (row / 3);
	uint8_t boxColumnStart = 3 * (column / 3);
	uint8_t value = getValue(row, column);

	for(uint8_t i = 0; i < ELEMENTS; i++) {
		board[row][i].clearPossibleValue(value); // removes value from possible values in row
		board[i][column].clearPossibleValue(value); // removes value from possible values in column
		board[boxRowStart + (i / 3)][boxColumnStart + (i % 3)].clearPossibleValue(value); // removes value from possible values in box
	}

}
void Board::set_possible_values(uint8_t input_value, uint8_t row, uint8_t column) {
	board[row][column].setPossibleValue(input_value);
}

// Uitility function definitions
bool isBoardSolved(Board &board) {
	return false;
}

bool isBoardValid(Board &board) {
	return false;
}

bool isColumnValid(Board &board) {
	return false;
}

bool isRowValid(Board &board) {
	return false;
}

bool isBoxValid(Board &board) {
	return false;
}