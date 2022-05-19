#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

#define F first
#define S second
#define PB push_back

using namespace std;


class Rook: public Piece{
    public:
        Rook(int i, int j, string color);

        Rook(string color);
        
        static const int numberOfPiecesForEachColor = 2;
        
        bool validMove(int i, int j);

        static pair<int, int>* black();

        static pair<int, int>* white();

        //return every possible move for the rook piece on live situation
        //first item in the array is a pair which it's first item is the length of the array
        pair<int, int>* moves(Piece* board[8][8]);

};

#endif