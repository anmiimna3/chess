#ifndef CELL_H
#define CELL_H

#include "piece.h"

enum StateOfCell{
    MATE,
    NONE,
    WIN,
    LOSE,
};

class Cell{
    RectangleShape rect;
    Piece* piece;
    StateOfCell state;

    void setColor(Color x);
};

#endif