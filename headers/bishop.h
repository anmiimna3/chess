#ifndef BISHOP_H
#define BISHOP_H

#include "piece.h"


class Bishop: public Piece{
    public:
        Bishop(int i, int j, string color);

        Bishop(string color);

        static const int numberOfPiecesForEachColor = 2;

        static pair<int, int>* black();

        static pair<int, int>* white();

        bool validMove(int i , int j);

        pair<int, int>* moves(Piece* board[8][8]);
};

#endif