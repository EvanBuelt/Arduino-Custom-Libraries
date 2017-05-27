#include <stdint.h>
#include "SolverSupport.h"
#include "SolverTriples.h"
#include "Board.h"

bool removeNakedTriples(Board &board) {
	bool removed = false;

	removed |= removeNakedTripleRow(board);
	removed |= removeNakedTripleColumn(board);
	removed |= removeNakedTripleBox(board);

	return removed;
}
bool removeHiddenTriples(Board &board) {
	bool removed = false;

	removed |= removeHiddenTripleRow(board);
	removed |= removeHiddenTripleColumn(board);
	removed |= removeHiddenTripleBox(board);

	return removed;
}
bool removePointingTriples(Board &board) {
	bool removed = false;

	removed |= removePointingTripleRow(board);
	removed |= removePointingTripleColumn(board);
	removed |= removePointingTripleBox(board);

	return removed;
}

bool removeNakedTripleRow(Board &board) {
	return false;
}
bool removeNakedTripleColumn(Board &board) {
	return false;
}
bool removeNakedTripleBox(Board &board) {
	return false;
}

bool removeHiddenTripleRow(Board &board) {
	return false;
}
bool removeHiddenTripleColumn(Board &board) {
	return false;
}
bool removeHiddenTripleBox(Board &board) {
	return false;
}

bool removePointingTripleRow(Board &board) {
	return false;
}
bool removePointingTripleColumn(Board &board) {
	return false;
}
bool removePointingTripleBox(Board &board) {
	return false;
}