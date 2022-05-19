#include "king.h"

King::King(int i, int j, string color)
    :Piece(i, j, color, "K"){}

King::King(string color)
    :Piece(color, "K"){}

bool King::badDistance(int i, int j, string color){
    if (color == "W"){
        int tempI = whiteKing->getPosition().F + i - blackKing->getPosition().F;
        int tempJ = whiteKing->getPosition().S + j - blackKing->getPosition().S;
        if ((tempI > -2 && tempI < 2) && (tempJ > -2 && tempJ < 2))
            return true;
        return false;
    }
    else{
        int tempI = blackKing->getPosition().F + i - whiteKing->getPosition().F;
        int tempJ = blackKing->getPosition().S + j - whiteKing->getPosition().S;
        if ((tempI > -2 && tempI < 2) && (tempJ > -2 && tempJ < 2))
            return true;
        return false;
    }
}

pair<int, int>* King::black(){
    pair<int, int> *black = new pair<int, int>[1];
    black[0] = {7, 4};
    return black;
}

pair<int, int>* King::white(){
    pair<int, int> *white = new pair<int, int>[1];
    white[0] = {0, 4};
    return white;
}

bool King::validMove(int i , int j){
    if (i > 1 || j > 1 || i < -1 || j < -1)
        return false;
    if (badDistance(i, j, getColor()))
        return false;
    return true;
}

pair<int, int>* King::moves(Piece* board[8][8]){
    pair<int, int> *moves = new pair<int, int>[9];
    int counter = 1;
    int x = getPosition().F, y = getPosition().S;
    for (int i = -1; i < 2; i++)
        for (int j = -1; j < 2; j++){
            if (j == 0 && i == 0)
                continue;
            if (validPosition(i, j) && !badDistance(i, j, getColor()) && board[x + i][y + j]->getColor() != getColor())
                moves[counter++] = {i, j};
        }
    moves[0] = {counter - 1, 0};
    return moves;
}