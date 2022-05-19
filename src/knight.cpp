#include "knight.h"

Knight::Knight(int i, int j, string color)
    :Piece(i, j, color, "N"){}

Knight::Knight(string color)
    :Piece(color, "N"){}

pair<int, int>* Knight::black(){
    pair<int, int> *black = new pair<int, int>[2];
    black[0] = {7, 1};
    black[1] = {7, 6};
    return black;
}

pair<int, int>* Knight::white(){
    pair<int, int> *white = new pair<int, int>[2];
    white[0] = {0, 1};
    white[1] = {0, 6};
    return white;
}

bool Knight::validMove(int i, int j){
    if ((i == 1 || i == -1) && (j == 2 || j == -2))
        return true;
    if ((i == 2 || i == -2) && (j == 1 || j == -1))
        return true;
    return false;
}

pair<int, int>* Knight::moves(Piece* board[8][8]){
    pair<int, int> *moves = new pair<int, int>[9];
    int counter = 1;
    int x = getPosition().F, y = getPosition().S; 
    int u[4] = {1, 2, -1, -2};
    for (int i : u)
        for (int j : u){
            if ((i + j) % 2 == 0)
                continue;
            if (validPosition(i, j) && board[x + i][y + j]->getColor() != getColor()){
                moves[counter++] = {i, j};
            }
        }
    moves[0] = {counter - 1, 0};
    return moves;
}