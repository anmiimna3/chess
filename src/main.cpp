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

    RenderWindow window(VideoMode(1000, 818), "chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    Board board(&window);
    board.run();
}