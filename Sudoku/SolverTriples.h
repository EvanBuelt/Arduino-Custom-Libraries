#ifndef SOLVER_TRIPLES_H_
#define SOLVER_TRIPLES_H_

class Board;

bool removeNakedTriples(Board &board);
bool removeHiddenTriples(Board &board);
bool removePointingTriples(Board &board);

bool removeNakedTripleRow(Board &board);
bool removeNakedTripleColumn(Board &board);
bool removeNakedTripleBox(Board &board);

bool removeHiddenTripleRow(Board &board);
bool removeHiddenTripleColumn(Board &board);
bool removeHiddenTripleBox(Board &board);

bool removePointingTripleRow(Board &board);
bool removePointingTripleColumn(Board &board);
bool removePointingTripleBox(Board &board);

#endif