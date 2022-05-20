#include "templates.h"

Costume::~Costume(){};

Costume::Costume(){};

int Consts::cellSize = 100;
pair<Color, Color> Consts::cellColor = {Color::Black, Color::White};
Color Consts::selected = Color::Cyan;
Color Consts::check = Color::Red;