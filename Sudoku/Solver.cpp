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
		running |= removeNakedDoubles(*board);
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
