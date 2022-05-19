#ifndef CELL_H
#define CELL_H

#include "piece.h"

struct Cell{
    RectangleShape rect;
    Piece* piece;
};

#endif