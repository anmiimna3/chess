#include "null.h"

Null::Null():Piece("-", "-"){}

Null::Null(int i, int j)
    :Piece(i, j, "-", "-"){}