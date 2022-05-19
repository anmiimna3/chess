#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"


class Knight: public Piece{
    public:
        Knight(int i, int j, string color);

        Knight(string color);

        static const int numberOfPiecesForEachColor = 2;

        static pair<int, int>* black();

        static pair<int, int>* white();

        bool validMove(int i, int j);

        pair<int, int>* moves(Piece* board[8][8]);
};

#endif