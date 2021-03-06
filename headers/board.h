#ifndef BOARD_H
#define BOARD_H


#include "includes.h"
#include "templates.h"
#include "translate.h"
#include <vector>



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
        Text status, readButtonText, resetButtonText, beforeButtonText, afterButtonText;
        Font font;
        RectangleShape resetButton, readButton, beforeButton, afterButton;
        SoundBuffer buffer[5];
        Sound sound[5];
        vector<singleMove> allMoves;
        vector<singleMove> temp;
        Texture sideBarT;
        Sprite sideBar;
        SoundBuffer backgroundMusicBuff;
        Sound backgroundMusic;
        map<string, Sprite*> globalPieces;
        map<string, Texture*> globalTextures;
        map<string, Vector2f> globalPiecePosition;
        bool isReading;
        King* whiteKing, *blackKing;
        int whiteKingCount, blackKingCount;
        Texture t;

        //Initializes the board for the first time
        void initialize();

        Vector2f generateCellPosition(int i, int j);

        void setCells();

        void initText();

        void setText();

        void defineButton(RectangleShape*, Text*, Vector2f, Vector2f, Color, Font*, int, Vector2f, Color, string);

        void drawText();

        void loadSound();

        void animate(pair<int, int>, pair<int, int>);

        void createButtons();

        void next();

        void previous();

        void playBackgroundMusic();

        void changeStatusOfButtons();

        string dragHandler(Vector2i);

        void moveGlobalSprint(Vector2i, string);

        void emptyBoard();

        bool drop(Vector2i, string);

        void loadingScreen();

        void emptyOneCell(int, int);

        void emptyOneCellv(Vector2i);
};

#endif