#ifndef SOLVER_DOUBLES_H_
#define SOLVER_DOUBLES_H_

class Board;

bool removeNakedDoubles(Board &board);
bool removeHiddenDoubles(Board &board);
bool removePointingDoubles(Board &board);

bool removeNakedDoubleRow(Board &board);
bool removeNakedDoubleColumn(Board &board);
bool removeNakedDoubleBox(Board &board);

bool removeHiddenDoubleRow(Board &board);
bool removeHiddenDoubleColumn(Board &board);
bool removeHiddenDoubleBox(Board &board);

bool removePointingDoubleRow(Board &board);
bool removePointingDoubleColumn(Board &board);
bool removePointingDoubleBox(Board &board);

bool processHiddenDouble(Board &board);
#endif