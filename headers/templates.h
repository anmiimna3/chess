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
    vector<string> pos;
    bool mate;
};

class Costume{
    public:
        template <typename T> 
        static void init(Board* board);

        template <typename T>
        static Piece* placing(Board* board, int i, int j, string color);
};