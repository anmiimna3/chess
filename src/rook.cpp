#include "rook.h"


Rook::Rook(int i, int j, string color)
    :Piece(i, j, color, "R"){}

Rook::Rook(string color)
    :Piece(color, "R"){}

bool Rook::validMove(int i, int j){
    if ((i != 0 && j != 0) || (i == 0 && j == 0))
        return false;
    return true;
}

pair<int, int>* Rook::black(){
    pair<int, int> *black = new pair<int, int>[2];
    black[0] = {7, 0};
    black[1] = {7, 7};
    return black;
}

pair<int, int>* Rook::white(){
    pair<int, int> *white = new pair<int, int>[2];
    white[0] = {0, 0};
    white[1] = {0, 7};
    return white;
}

pair<int, int>* Rook::moves(Piece* board[8][8]){
    string opponentColor = getColor() == "W"? "B" : "W";
    pair<int, int> *moves = new pair<int, int>[29];
    int counter = 1;
    bool found[4] = {0};
    int x = getPosition().F, y = getPosition().S;
    for (int i = 1; i < 8; i++){

        if (liniar(found, 0, x, y, 0, i, board))
            moves[counter++] = {0, i};
        if (liniar(found, 1, x, y, 0, -i, board))
            moves[counter++] = {0, -i};
        if (liniar(found, 2, x, y, i, 0, board))
            moves[counter++] = {i, 0};
        if (liniar(found, 3, x, y, -i, 0, board))
            moves[counter++] = {-i, 0};
    }
    moves[0] = {counter - 1, 0};
    return moves;
}