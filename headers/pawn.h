#pragma once
#include "piece.h"

#define F first
#define S second
#define PB push_back

using namespace std;



class Pawn: public Piece{
    public:
        Pawn(int i, int j, string color);

        Pawn(string color);

        static const int numberOfPiecesForEachColor = 8;

        static pair<int, int>* black();

        static pair<int, int>* white();

        bool validMove(int i, int j);

        bool validTake(int i, int j);

        pair<int, int>* moves(Piece* board[8][8]);
};
