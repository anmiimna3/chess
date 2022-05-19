#include "pawn.h"

Pawn::Pawn(int i, int j, string color)
    :Piece(i, j, color, "P"){}

Pawn::Pawn(string color)
    :Piece(color, "P"){}

pair<int, int>* Pawn::black(){
    pair<int, int> *black = new pair<int, int>[8];
    for (int i = 0; i < 8; i++)
        black[i] = {6, i};
    return black;
}

pair<int, int>* Pawn::white(){
    pair<int, int> *white = new pair<int, int>[8];
    for (int i = 0; i < 8; i++)
        white[i] = {1, i};
    return white;
}

bool Pawn::validMove(int i, int j){
    if (j != 0)
        return false;
    if (i == 1 && getColor() == "W")
        return true;
    if (i == 2 && getColor() == "W" && getPosition().F == 1)
        return true;
    if (i == -1 && getColor() == "B")
        return true;
    if (i == -2 && getColor() == "B" && getPosition().F == 6)
        return true;
    return false;
}

bool Pawn::validTake(int i, int j){
    if (j != 1 && j != -1)
        return false;
    if (i == 1 && getColor() == "W")
        return true;
    if (i == -1 && getColor() == "B")
        return true;
    return false;
}

pair<int, int>* Pawn::moves(Piece* board[8][8]){
    string opponentColor = getColor() == "W" ? "B" : "W";
    pair<int, int> *moves = new pair<int, int>[5];
    int counter = 1;
    int x = getPosition().F, y = getPosition().S;
    if (x == 7 || x == 0){
        moves[0] = {0, 0};
        return moves;
    }
    if (getColor() == "W"){
        if (board[x + 1][y]->getColor() == "-")
            moves[counter++] = {1, 0};
        if (board[x + 1][y + 1]->getColor() == opponentColor && y != 7)
            moves[counter++] = {1, 1};
        if (board[x + 1][y - 1]->getColor() == opponentColor && y != 0)
            moves[counter++] = {1, -1};
        if (getPosition().F == 1 && board[x + 2][y]->getColor() == "-" && board[x + 1][y]->getColor() == "-")
            moves[counter++] = {2, 0};
        moves[0] = {counter - 1, 0};
    }
    else{
        if (board[x - 1][y]->getColor() == "-"){
            moves[counter++] = {-1, 0};
        }
        if (board[x - 1][y + 1]->getColor() == opponentColor && y != 7){
            moves[counter++] = {-1, 1};
        }
        if (board[x - 1][y - 1]->getColor() == opponentColor && y != 0){
            moves[counter++] = {-1, -1};
        }
        if (getPosition().F == 6 && board[x - 2][y]->getColor() == "-" && board[x - 1][y]->getColor() == "-"){
            moves[counter++] = {-2, 0};
        }
        moves[0] = {counter - 1, 0};
    }
    return moves;
}