#include "queen.h"

Queen::Queen(int i, int j, string color)
    :Piece(i, j, color, "Q"){}

Queen::Queen(string color)
    :Piece(color, "Q"){}

pair<int, int>* Queen::black(){
    pair<int, int> *black = new pair<int, int>[1];
    black[0] = {7, 3};
    return black;
}

pair<int, int>* Queen::white(){
    pair<int, int> *white = new pair<int, int>[1];
    white[0] = {0, 3};
    return white;
}

bool Queen::validMove(int i, int j){
    if (i == 0 || j == 0)
        return true;
    if (i == j || i == -j)
        return true;
    return false;
}

pair<int, int>* Queen::moves(Piece* board[8][8]){
    string opponentColor = getColor() == "W" ? "B" : "W";
    pair<int, int> *moves = new pair<int, int>[29];
    int counter = 1;
    int x = getPosition().F, y = getPosition().S;
    bool found[4] = {0};
    int sign[] = {1, -1};
    for (int j: sign){
        for (int i = 1; i < 8; i++){
            if (liniar(found, 0, x, y, j * i, 0, board))
                moves[counter++] = {j * i, 0};
            if (liniar(found, 1, x, y, 0, j * i, board))
                moves[counter++] = {0, j * i};
            if (liniar(found, 2, x, y, j * i, j * i, board))
                moves[counter++] = {j * i, j * i};
            if (liniar(found, 3, x, y, j * i, -(j * i), board))
                moves[counter++] = {j * i, j * (-i)};
        }
        for (int i = 0; i < 4; i++)
            found[i] = 0;
    }
    moves[0] = {counter - 1, 0};
    return moves;
}