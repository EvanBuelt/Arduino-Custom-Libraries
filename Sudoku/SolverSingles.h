#ifndef SOLVER_SINGLES_H_
#define SOLVER_SINGLES_H_

class Board;

bool removeNakedSingles(Board &board);
bool removeHiddenSingles(Board &board);

bool removeHiddenSingleRow(Board &board);
bool removeHiddenSingleColumn(Board &board);
bool removeHiddenSingleBox(Board &board);

bool processHiddenSingle(Board &board);
#endif