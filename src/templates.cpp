#include "templates.h"

Costume::~Costume(){};

Costume::Costume(){};

int Consts::cellSize = 100;
int Consts::cellOffset = 3;
int Consts::indexRow = 40;
pair<Color, Color> Consts::cellColor = {Color(181, 135, 99), Color(241, 217, 181)};
Color Consts::selected = Color::Cyan;
Color Consts::check = Color(225, 0, 59);
Color Consts::possibleToMove = Color::Cyan;
Color Consts::finallywin = Color(3, 172, 19);
Color Consts::finallyLose = Color(255, 223, 0);
Color Consts::background = Color(51, 46, 43);
Color Consts::buttons = Color(220, 209, 104);
