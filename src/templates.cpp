#include "templates.h"

Costume::~Costume(){};

Costume::Costume(){};


// template <typename T> 
// void Costume::init(Board* board){
//     int count = T::numberOfPiecesForEachColor;
//     pair<int, int>* black = T::black();
//     pair<int, int>* white = T::white();
//     for (int i = 0; i < count; i++){
//         T* n = new T("B");
//         board->place((Piece*) n, black[i].F, black[i].S);
//     }
//     for (int i = 0; i < count; i++){
//         T* n = new T("W");
//         board->place((Piece*) n, white[i].F, white[i].S);
//     }
// }

// template <typename T>
// Piece* Costume::placing(Board* board, int i, int j, string color){
//     T* t = new T(color);
//     board->place(t, i, j);
//     return t;
// }