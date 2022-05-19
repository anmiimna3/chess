#ifndef KING_H
#define KING_H

#include "piece.h"


class King: public Piece{
    public:
        King(int i, int j, string color);

        King(string color);

        static const int numberOfPiecesForEachColor = 1;
        // static pair<int, int> whitePosition;
        // static pair<int, int> blackPosition;

        bool badDistance(int i, int j, string color);

        King* whiteKing;
        King* blackKing;

        static pair<int, int>* black();

        static pair<int, int>* white();

        bool validMove(int i , int j);
        
        pair<int, int>* moves(Piece* board[8][8]);
};

#endif