#include "piece.h"
#include "templates.h"


map<string, Texture*> save;

Piece::~Piece(){}

Piece::Piece(): Name("-"), Color("-"){
    loadTexture();
}

Piece::Piece(string color, string name)
:Name(name), Color(color){
    loadTexture();        
}

Piece::Piece(int i, int j, string color, string name)
: Name(name), Color(color){
    Position = {i, j};
    loadTexture();
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
    
void Piece::loadTexture(){
    if (Name == "-")
        return;
    if (save.find(getTitle()) == save.end()){
        Texture* texture = new Texture;
        if (!texture->loadFromFile("./resources/images/" + getTitle() + ".png"))
            cerr << "error\n";
        texture->setSmooth(true);
        save.insert({getTitle(), texture});
    }
    sprite.setTexture(*save.at(getTitle()));
    sprite.setPosition(generateCellPosition(Position.F, Position.S));
    float pieceScaleX = (float) Consts::cellSize / sprite.getTexture()->getSize().x;
    float pieceScaleY = (float) Consts::cellSize / sprite.getTexture()->getSize().y;
    sprite.setScale(pieceScaleX, pieceScaleY);
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

Sprite Piece::getSprite(){
    return sprite;
}

void Piece::setPosition(pair<int, int> pos){
    Position = pos;
    sprite.setPosition(generateCellPosition(7 - Position.F, Position.S));
}

Vector2f Piece::generateCellPosition(int i, int j){
    return Vector2f(j * Consts::cellSize + (j - 1) * Consts::cellOffset + Consts::indexRow, i * Consts::cellSize + (i - 1) * Consts::cellOffset);
}

void Piece::moveSprite(int i, int j){
    Vector2f temp = sprite.getPosition();
    sprite.setPosition(Vector2f(temp.x + i, temp.y + j));
}