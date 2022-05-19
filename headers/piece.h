#ifndef PIECE_H
#define PIECE_H

#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>

#define F first
#define S second

using namespace sf;
using namespace std;



class Piece{
    friend ostream& operator<< (ostream& stream, const Piece& piece);
    public:
        virtual ~Piece();
        
        Piece();

        Piece(string color, string name);

        Piece(int i, int j, string color, string name);

        bool liniar(bool found[4], int index, int x, int y, int i, int j, Piece* board[8][8]);


        virtual pair<int, int>* moves(Piece* board[8][8]);

        //checks if the move is valid for taking for a specific piece
        //also checks if the move isn't out of bounds for the 8x8 board
        virtual bool validTake(int i, int j);

        //checks if the move is valid by that specific piece
        //also checks if the move isn't out of bounds for the 8x8 board
        virtual bool validMove(int i, int j);

        //checks if after the move, piece is still on the board
        bool validPosition(int i, int j);
        
        pair<int, int> getPosition();

        string getTitle();

        string getColor();

        string getName();

        virtual void setPosition(pair<int, int> pos);
    private:
        const string Color;
        const string Name;
        pair<int, int> Position;
};

#endif