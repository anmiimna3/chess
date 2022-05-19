#pragma once
#include "piece.h"

class Queen: public Piece{
    public:
        Queen(int i, int j, string color);

        Queen(string color);
        
        static const int numberOfPiecesForEachColor = 1;

        static pair<int, int>* black();

        static pair<int, int>* white();

        bool validMove(int i, int j);

        pair<int, int>* moves(Piece* board[8][8]);
};
