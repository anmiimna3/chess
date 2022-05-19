#include "piece.h"

Piece::~Piece(){}

Piece::Piece(): Name("-"), Color("-"){}

Piece::Piece(string color, string name)
    :Name(name), Color(color){}

Piece::Piece(int i, int j, string color, string name)
    : Name(name), Color(color){
        Position = {i, j};
    }

bool Piece::liniar(bool found[4], int index, int x, int y, int i, int j, Piece* board[8][8]){
        if (found[index]){
            return false;
        }
        if (!validPosition(i, j)){
            found[index] = 1;
            return false;
        }
        string name = board[x + i][y + j]->getColor();
        if (name == Color){
            found[index] = 1;
            return false;
        }
        if (name != "-")
            found[index] = 1;
        return true;
    }

pair<int, int>* Piece::moves(Piece* board[8][8]){}

bool Piece::validTake(int i, int j){
        return validMove(i, j);
    }

bool Piece::validMove(int i, int j){}

bool Piece::validPosition(int i, int j){
        int tempI = i + getPosition().F, tempJ = j + getPosition().S;
        if (tempI > 7 || tempI < 0 || tempJ > 7 || tempJ < 0)
            return false;
        return true;
    }
    
pair<int, int> Piece::getPosition(){
        return Position;
    }

string Piece::getTitle(){
        return Name + Color; 
    }

string Piece::getColor(){
        return Color;
    }

string Piece::getName(){
        return Name;
    }

void Piece::setPosition(pair<int, int> pos){
        Position = pos;
    }