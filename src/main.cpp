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
    auto image = Image();
    image.loadFromFile("./resources/images/icon.jpg");
    RenderWindow window(VideoMode(1000 + Consts::indexRow, 812 + Consts::indexRow), "chess", Style::Titlebar | Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    Board board(&window);
    board.run();
}