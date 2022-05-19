#include "bishop.h"

Bishop::Bishop(int i, int j, string color)
    :Piece(i, j, color, "B"){}

Bishop::Bishop(string color)
    :Piece(color, "B"){}

pair<int, int>* Bishop::black(){
    pair<int, int> *black = new pair<int, int>[2];
    black[0] = {7, 2};
    black[1] = {7, 5};
    return black;
}

pair<int, int>* Bishop::white(){
    pair<int, int> *white = new pair<int, int>[2];
    white[0] = {0, 2};
    white[1] = {0, 5};
    return white;
}

bool Bishop::validMove(int i , int j){
    if (i != j && i != -j)
        return false;
    return true;
}

pair<int, int>* Bishop::moves(Piece* board[8][8]){
    string opponentColor = getColor() == "W" ? "B" : "W";
    pair<int, int> *moves = new pair<int, int>[15];
    int x = getPosition().F, y = getPosition().S;
    bool found[4] = {0};
    int counter = 1;
    for (int i = 1; i < 8; i++){
        if (liniar(found, 0, x, y, i, i, board))
            moves[counter++] = {i, i};
        if (liniar(found, 1, x, y, i, -i, board))
            moves[counter++] = {i, -i};
        if (liniar(found, 2, x, y, -i, i, board))
            moves[counter++] = {-i, i};
        if (liniar(found, 3, x, y, -i, -i, board))
            moves[counter++] = {-i, -i};
    }
    moves[0] = {counter - 1, 0};
    return moves;
}