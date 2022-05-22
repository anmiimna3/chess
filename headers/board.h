#ifndef BOARD_H
#define BOARD_H


#include "includes.h"
#include "templates.h"
#include "translate.h"



class Board{
    public:
        Board(RenderWindow* _window);

        Board(bool custom);

        Board(Piece* board[8][8], string turn);

        void show();

        //swaps two cell's objects
        //if positions are out of bound returns false O.W returns true
        bool swap(pair<int, int> a, pair<int, int> b);

        //places a pointer to Piece on board[x][y]
        //returns the pointer to Piece which was on board[x][y] before the placement
        Piece* place(Piece* piece, int x, int y);

        Piece* take(pair<int, int> a, pair<int, int> b);

        movement backtrack0(int, int);

        movement backtrack1(int, int);

        movement backtrack2();

        movement backtrack3();

        void undo(pair<int, int> a, pair<int, int> b, Piece *piece);

        //checks for checkmate situation by turn
        //return a boolean
        bool Mate(string opponentColor, string turn);
        
        bool checkAfterMove(Piece* piece, int p, int q, string opponentColor, string turn);

        //checks whether that the turn color made the check situation
        //returns a boolean
        //takes one argument the color of the player who made move for check. it's either "W" or "B"
        bool check(string turn);

        bool straightcheck(int p, int q,int a, int b, string pieces[], int size, string turn);

        stats move(pair<int, int> a, pair<int, int> b);

        void changeTurn();
        
        Piece* getPiece(int i, int j);

        string getTurn();

        void setTurn(char turn);

        string getOpponentColor();

        void read();

        void run();

        void draw();

        void mouseClicked(Vector2i v);

        void resetCellColors();

    private:
        Piece* board[8][8];
        Cell* display[8][8];
        string turn;
        RenderWindow *window;
        pair<int, int> selectedPiece;
        bool selected;
        pair<int, int> checkedCell;
        bool ended;

        //Initializes the board for the first time
        void initialize();

        Vector2f generateCellPosition(int i, int j);

        void setCells();
};

#endif