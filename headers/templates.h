#ifndef TEMPLATES_H
#define TEMPLATES_H

#include "piece.h"
#include <vector>

class Board;

struct stats{
    Piece* piece;
    bool mate;
    bool valid;
    bool full;
};

struct movement{
    vector<pair<int, int>> pos;
    bool mate;
};

struct Consts{
    static int cellSize;
    static int cellOffset;
    static int indexRow;
    static pair<Color, Color> cellColor;
    static Color selected;
    static Color check;
    static Color possibleToMove;
    static Color finallywin;
    static Color finallyLose;
};


struct singleMove{
    pair<int, int> start;
    pair<int, int> finish;
    Piece* piece;
};


class Costume{
    public:
        virtual ~Costume();

        Costume();

        template <typename T> 
        static void init(Board* board){
            int count = T::numberOfPiecesForEachColor;
            pair<int, int>* black = T::black();
            pair<int, int>* white = T::white();
            for (int i = 0; i < count; i++){
                T* n = new T("B");
                board->place((Piece*) n, black[i].F, black[i].S);
            }
            for (int i = 0; i < count; i++){
                T* n = new T("W");
                board->place((Piece*) n, white[i].F, white[i].S);
            }
        }

        template <typename T>
        static Piece* placing(Board* board, int i, int j, string color){
            T* t = new T(color);
            board->place((Piece*) t, i, j);
            return t;
        }
};

#endif