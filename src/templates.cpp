#include "templates.h"

Costume::~Costume(){};

Costume::Costume(){};

int Consts::cellSize = 100;
int Consts::cellOffset = 3;
int Consts::indexRow = 40;
pair<Color, Color> Consts::cellColor = {Color(241, 217, 181), Color(181, 135, 99)};
Color Consts::selected = Color::Cyan;
Color Consts::check = Color::Red;
Color Consts::possibleToMove = Color::Cyan;
Color Consts::finallywin = Color::Blue;
Color Consts::finallyLose = Color::Yellow;
Color Consts::background = Color(51, 46, 43);
