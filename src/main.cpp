#include "main.h"

ostream& operator<< (ostream& stream, const Piece& piece){
    stream << piece.Name << piece.Color;
    return stream;
}


void sort(vector<string> &v){
    for (int i = 0; i < v.size(); i++)
        for (int j = i + 1; j < v.size(); j++){
            if (v[i] > v[j])
                swap(v[i], v[j]);
        }
}

int main(){

    RenderWindow window(VideoMode(818, 818), "chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    Board board(&window);
    board.run();
}




// Board gameBoard = Board(1);
// string mode;
// cin >> mode;
// gameBoard.setTurn(mode[0]);
// gameBoard.read();
// if (mode[1] == 'D'){
//     vector<string> v = gameBoard.backtrack0().pos;
//     sort(v);
//     for (auto u: v)
//         cout << u << endl;
//     if (v.size() == 0)
//         cout << "No Answer!";
// }
// else{
//     vector<string> v = gameBoard.backtrack1().pos;
//     sort(v);
//     for (auto u: v)
//         cout << u << endl;
//     if (v.size() == 0)
//         cout << "No Answer!";
// }