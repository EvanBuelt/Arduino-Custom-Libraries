#include "Solver.h"

#include "SolverSingles.h"
#include "SolverDoubles.h"
#include "SolverTriples.h"
#include "SolverQuads.h"

#include "arduino.h"
ElegantSolver::ElegantSolver(Board *inputBoard) {
	board = inputBoard;
	solverSupport.setBoard(board);

}

void ElegantSolver::solve() {
	bool running = true;

	while(running) {
		running = false;

		// Call functions that look for two possible values in row, column, box, or pair of cells
		//running |= removeNakedDoubles(*board);
		//running |= removeHiddenDoubles(*board);
		//running |= removePointingDoubles(*board);

		// Call functions that look for two-three possible values in row, column, box, or triplet of cells
		//running |= removeNakedTriples(*board);
		//running |= removeHiddenTriples(*board);
		//running |= removePointingTriples(*board);

		// Call functions that look for single possible value in row, column, box, or cell
		running |= removeNakedSingles(*board);
		running |= removeHiddenSingles(*board);
		Serial.println("Looping");

	}
}


// Utility Functions

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
		}*/
	}
	return found;
}
