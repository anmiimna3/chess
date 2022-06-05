#include "board.h"
#include "SFML/Audio.hpp"
#include <sstream>
// #include <sfeMovie/Movie.hpp>

Board::Board(RenderWindow* _window){
    window = _window;
    loadingScreen();
    checkedCell = {-1, -1};
    ended = false;
    loadSound();
    createButtons();
    setCells();
    initText();
    turn = "W";
    isReading = false;
}
Board::Board(bool custom){
    setCells();
    turn = "W";
    isReading = false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            Null* null = new Null();
            place(null, i, j);
        }
}

Board::Board(Piece* board[8][8], string turn){
    setCells();
    isReading = false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            place(board[i][j], i, j);
    this->turn = turn;
}

void Board::show(){
    for (int i = 7; i >= 0; i--){
        for (int j = 0; j < 8; j++){
            cout << *board[i][j] << " ";
        }
        cout << "\n";
    }
}

//swaps two cell's objects
//if positions are out of bound returns false O.W returns true
bool Board::swap(pair<int, int> a, pair<int, int> b){
    if (a.S > 7 || a.F > 7 || b.S > 7 || b.F > 7)
        return false;
    if (a.S < 0 || a.F < 0 || b.S < 0 || b.F < 0)
        return false;
    Piece* pieceA = place(board[a.F][a.S], b.F, b.S);
    place(pieceA, a.F, a.S);
    return true;
}

//places a pointer to Piece on board[x][y]
//returns the pointer to Piece which was on board[x][y] before the placement
Piece* Board::place(Piece* piece, int x, int y){
    Piece* temp = board[x][y];
    piece->setPosition({x, y});
    board[x][y] = piece;
    return temp;
}

Piece* Board::take(pair<int, int> a, pair<int, int> b){
    Null* null = new Null();
    Piece* piece = place(board[a.F][a.S], b.F, b.S);
    place(null, a.F, a.S);
    return piece;
}

movement Board::backtrack0(int i, int j){
    movement answer;
    if (board[i][j]->getColor() == turn){
        Piece* piece = board[i][j];
        pair<int, int> *moves = piece->moves(board);
        for (int k = 1; k < moves[0].F + 1; k++){
            stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
            if (!status.valid)
                continue;
            for (int ii = 0; ii < 8; ii++)
                for (int jj = 0; jj < 8; jj++){
                    if (status.mate || backtrack1(ii, jj).pos.size() != 0)
                        answer.pos.PB({i + moves[k].F, j + moves[k].S});
                        // temp.PB(Translate::toString({i, j}, {i + moves[k].F, j + moves[k].S}, piece->getTitle()));
                }
            undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
        }
    }
    return answer;
}


movement Board::backtrack1(int i, int j){
    movement answer;
    if (board[i][j]->getColor() == turn){
        Piece *piece = board[i][j];
        pair<int, int> *moves = piece->moves(board);
        for (int k = 1; k < moves[0].F + 1; k++){
            stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
            if (!status.valid)
                continue;
            if (status.mate || backtrack2().mate)
                answer.pos.PB({i + moves[k].F, j + moves[k].S});
            undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
        }
    }
    return answer;
}

movement Board::backtrack2(){
    movement answer;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            if (board[i][j]->getColor() == turn){
                Piece *piece = board[i][j];
                pair<int, int> *moves = piece->moves(board);
                for (int k = 1; k < moves[0].F + 1; k++){
                    stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
                    if (!status.valid)
                        continue;
                    if (status.mate){
                        undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                        answer.mate = false;
                        return answer;
                    }
                    else{
                        if (!backtrack3().mate){
                            undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                            answer.mate = false;
                            return answer;
                        }
                    }
                    undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                }
            }
        }
    answer.mate = true;
    return answer;                
}

movement Board::backtrack3(){
    movement answer;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            if (board[i][j]->getColor() == turn){
                Piece *piece = board[i][j];
                pair<int, int> *moves = piece->moves(board);
                for (int k = 1; k < moves[0].F + 1; k++){
                    stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
                    if (!status.valid)
                        continue;
                    if (status.mate){
                        undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                        answer.mate = true;
                        return answer;
                    }
                    undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                }
            }
        }
    answer.mate = false;
    return answer;
}

void Board::undo(pair<int, int> a, pair<int, int> b, Piece *piece){
    swap(a, b);
    place(piece, b.F, b.S);
    changeTurn();
}


//checks for checkmate situation by turn
//return a boolean
bool Board::Mate(string opponentColor, string turn){
    if (!check(turn))
        return false;
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            if (board[i][j]->getColor() == opponentColor){
                Piece* piece = board[i][j];
                if (!checkAfterMove(piece, i, j, opponentColor, turn))
                    return false;
            }
        }
    return true;
}

bool Board::checkAfterMove(Piece* piece, int p, int q, string opponentColor, string turn){
    pair<int, int>* moves = piece->moves(board);
    for (int i = 1; i < moves[0].F + 1; i++){
        if (board[p + moves[i].F][q + moves[i].S]->getColor() == opponentColor)
            continue;
        if (board[p + moves[i].F][q + moves[i].S]->getColor() == "-"){
            swap({p, q}, {p + moves[i].F, q + moves[i].S});
            if (!check(turn)){
                swap({p, q}, {p + moves[i].F, q + moves[i].S});
                return false;
            }
            swap({p, q}, {p + moves[i].F, q + moves[i].S});
        }
        else{
            if (!(piece->validTake(moves[i].F, moves[i].S))){
                continue;
            }
            Piece* temp = take({p, q}, {p + moves[i].F, q + moves[i].S});
            if (!check(turn)){
                swap({p, q}, {p + moves[i].F, q + moves[i].S});
                place(temp, p + moves[i].F, q + moves[i].S);
                return false;
            }
            swap({p, q}, {p + moves[i].F, q + moves[i].S});
            place(temp, p + moves[i].F, q + moves[i].S);
        }   
    }
    return true;
}

//checks whether that the turn color made the check situation
//returns a boolean
//takes one argument the color of the player who made move for check. it's either "W" or "B"
bool Board::check(string turn){
    string opponentColor = (turn == "W" ? "B" : "W");
    bool found = false;
    int p, q;
    for (int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++)
            if (board[i][j]->getName() == "K" && board[i][j]->getColor() == opponentColor){
                p = i, q = j;
                found = true;
                break;
            }
        if (found)
            break;
    }
    if (!found)
        return false;
    if (board[p][q]->getColor() == "W"){
        if (p + 1 < 8 && q + 1 < 8){
            string temp1 = board[p + 1][q + 1]->getName() + board[p + 1][q + 1]->getColor();
            if (temp1 == "PB"){
                return true;
            }
        }
        if (p + 1 < 8 && q - 1 > -1){
            string temp2 = board[p + 1][q - 1]->getName() + board[p + 1][q - 1]->getColor();
            if (temp2 == "PB"){
                return true;
            }
        }
    }
    else{
        if (p - 1 > -1 && q + 1 < 8){
            string temp1 = board[p - 1][q + 1]->getName() + board[p - 1][q + 1]->getColor();
            if (temp1 == "PW"){
                return true;
            }
        }
        if (p - 1 > -1 && q - 1 > -1){
            string temp2 = board[p - 1][q - 1]->getName() + board[p - 1][q - 1]->getColor();
            if (temp2 == "PW"){
                return true;
            }
        }
    }
    int x[] = {1, 2, -1, -2};
    for (int i: x)
        for (int j: x){
            if ((i + j) % 2 == 0)
                continue;
            if (p + i > 7 || p + i < 0 || q + j > 7 || q + j < 0)
                continue;
            if (board[p + i][q + j]->getName() == "N" && board[p + i][q + j]->getColor() == turn){
                return true;
            }
        }
    
    string straight[] = {"R", "Q"};
    string diagonal[] = {"Q", "B"};
    if (straightcheck(p, q, 1, 0, straight, 2, turn) || straightcheck(p, q, 0, 1, straight, 2, turn) ||
        straightcheck(p, q,-1, 0, straight, 2, turn) || straightcheck(p, q, 0,-1, straight, 2, turn) ||
        straightcheck(p, q, 1, 1, diagonal, 2, turn) || straightcheck(p, q, 1,-1, diagonal, 2, turn) ||
        straightcheck(p, q,-1, 1, diagonal, 2, turn) || straightcheck(p, q,-1,-1, diagonal, 2, turn))
        return true;

    return false;            
}

bool Board::straightcheck(int p, int q,int a, int b, string pieces[], int size, string turn){
    string tempName;
    for (int i = 1; i < 8; i++){
        if (p + i * a > -1 && p + i * a < 8 && q + i * b > -1 && q + i * b < 8)  
            if (board[p + i * a][q + i * b]->getName() != "-"){
                if (board[p + i * a][q + i * b]->getColor() == turn){
                    tempName = board[p + i * a][q + i * b]->getName();
                    for (int cnt = 0; cnt < size; cnt++)
                        if (tempName == pieces[cnt]){
                            return true;
                        }
                }
                return false;
            }
    }
    return false;
}

stats Board::move(pair<int, int> a, pair<int, int> b){
    stats ans;
    ans.full = false;
    if (board[b.F][b.S]->getColor() == turn){
        ans.valid = false;
        return ans;
    }
    if (board[b.F][b.S]->getColor() == "-"){
        if (board[a.F][a.S]->validMove(b.F - a.F, b.S - a.S)){
            swap(a, b);
            ans.piece = board[a.F][a.S];
            changeTurn();
            if (check(turn)){
                changeTurn();
                swap(a, b);
                ans.valid = false;
                ans.full = true;
                return ans;
            }
            ans.valid = true;
            if (Mate(turn, getOpponentColor())){
                ans.mate = true;
                return ans;
            }
            ans.mate = false;
            return ans;
        }
        ans.valid = false;
        return ans;
    }
    if (board[a.F][a.S]->validTake(b.F - a.F, b.S - a.S)){
        Piece* temp = take(a, b);
        ans.piece = temp;
        changeTurn();
        if (check(turn)){
            swap(a, b);
            place(temp, b.F, b.S);
            changeTurn();
            ans.valid = false;
            ans.full = true;
            return ans;
        }
        ans.valid = true;
        if (Mate(turn, getOpponentColor())){
            ans.mate = true;
            return ans;
        }
        ans.mate = false;
        return ans;
    }
    ans.valid = false;
    return ans;
}

void Board::changeTurn(){
    turn = turn == "W" ? "B" : "W";
}

Piece* Board::getPiece(int i, int j){
    return board[i][j];
}

string Board::getTurn(){
    return turn;
}

void Board::setTurn(char turn){
    this->turn = turn;
}

string Board::getOpponentColor(){
    return (turn == "W" ? "B" : "W");
}

void Board::read(){
    string temp;
    Piece *tmp, *ex;
    King *white, *black;
    for (int i = 7; i > -1; i--){
        for (int j = 0; j < 8; j++){
            ex = board[i][j];
            cin >> temp;
            if (temp != "--"){
                string pieceColor = "";
                pieceColor += temp[1];
                if (temp[0] == 'P')
                    Costume::placing<Pawn>(this, i, j, pieceColor);
                if (temp[0] == 'R')
                    Costume::placing<Rook>(this, i, j, pieceColor);
                if (temp[0] == 'B')
                    Costume::placing<Bishop>(this, i, j, pieceColor);
                if (temp[0] == 'N')
                    Costume::placing<Knight>(this, i, j, pieceColor);
                if (temp[0] == 'Q')
                    Costume::placing<Queen>(this, i, j, pieceColor);
                if (temp[0] == 'K'){
                    tmp = Costume::placing<King>(this, i, j, pieceColor);
                    if (pieceColor == "W")
                        white = (King*) tmp;
                    else
                        black = (King*) tmp;
                }
            }
            else{
                Null* n = new Null();
                place((Piece*) n, i, j);
            }
            delete ex;
        }
    }
    white->whiteKing = white;
    white->blackKing = black;
    black->blackKing = black;
    black->whiteKing = white;
}

void Board::run(){
    initialize();
    window->display();
    bool globalPieceSelected = false;
    string globalPieceSelectedStr = "";
    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            playBackgroundMusic();
            if (event.type == Event::Closed){
                window->close();
            }
            if (isReading){
                if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !globalPieceSelected){
                    globalPieceSelectedStr = dragHandler(Mouse::getPosition(*window));
                    if (globalPieceSelectedStr != "")
                        globalPieceSelected = true;
                }
                if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left && globalPieceSelected){
                    bool x = drop(Mouse::getPosition(*window), globalPieceSelectedStr);
                    if (x){
                        globalPieceSelectedStr = "";
                        globalPieceSelected = false;
                    }
                }
                if (event.type == Event::MouseMoved && globalPieceSelected){
                    moveGlobalSprint(Mouse::getPosition(*window), globalPieceSelectedStr);
                }
                continue;
            }
            bool lock;
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left && !lock){
                lock = 1;
                mouseClicked(Mouse::getPosition(*window));
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::XButton1 && !lock){
                lock = 1;
                previous();
            }
            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::XButton2 && !lock){
                lock = 1;
                next();
            }
            if (event.type == Event::MouseButtonReleased && lock)
                lock = 0;
        }
        draw();
        window->display();
    }
}

void Board::drawText(){
    window->draw(status);
    window->draw(resetButton);
    window->draw(readButton);
    window->draw(beforeButton);
    window->draw(afterButton);
    window->draw(resetButtonText);
    window->draw(readButtonText);
    window->draw(beforeButtonText);
    window->draw(afterButtonText);
    if (isReading){
        string x[6] = {"R", "B", "P", "K", "Q", "N"};
        string y[2] = {"W", "B"};
        for (auto u: x)
            for (auto v: y)
                window->draw(*globalPieces.at(u + v));
    }
}


void Board::draw(){
    window->clear(Consts::background);
    setText();
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            window->draw(display[i][j]->rect);

    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            if (board[i][j]->getName() != "-")
                window->draw(board[i][j]->getSprite());
    drawText();
    window->draw(sideBar);
}


void Board::mouseClicked(Vector2i v){
    if (v.x < 0 || v.y < 0)
        return;
    if (v.x > 830 + Consts::indexRow && v.x < 990 + Consts::indexRow && v.y > 100 && v.y < 160){
        allMoves.clear();
        temp.clear();
        changeStatusOfButtons();
        isReading = (isReading ? false : true);
        if (isReading){
            emptyBoard();
            King* k = new King(100, 100, "W");
            whiteKing = k;
            King* kk = new King(100, 100, "B");
            blackKing = kk;
            blackKingCount = 0;
            whiteKingCount = 0;
            ended = false;
            checkedCell = {-1, -1};
            resetCellColors();
            turn = "W";
        }
        else{
            whiteKing->whiteKing = whiteKing;
            whiteKing->blackKing = blackKing;
            blackKing->whiteKing = whiteKing;
            blackKing->blackKing = blackKing;
        }
        return;
    }
    if (v.x > 830 + Consts::indexRow && v.x < 990 + Consts::indexRow && v.y > 170 && v.y < 230){
        checkedCell = {-1, -1};
        isReading = true;
        changeStatusOfButtons();
        isReading = false;
        ended = false;
        allMoves.clear();
        temp.clear();
        selected = false;
        resetCellColors();
        initialize();
        turn = "W";
        return;
    }
    if (v.x > 830 + Consts::indexRow && v.x < 890 + Consts::indexRow && v.y > 240 && v.y < 300){
        if (isReading){
            turn = "B";
            beforeButtonText.setString("*");
            afterButtonText.setString("");
            return;
        }
        previous();
        return;
    }
    if (v.x > 930 + Consts::indexRow && v.x < 990 + Consts::indexRow && v.y > 240 && v.y < 300){
        if (isReading){
            turn = "W";
            beforeButtonText.setString("");
            afterButtonText.setString("*");
            return;
        }
        next();
        return;
    }
    if (ended)
        return;
    v.x -= Consts::indexRow;
    if (v.y < 0 || v.x < 0)
        return;
    int selectX = v.x / 103, selectY = v.y / 103;
    if (selectX > 7 || selectY > 7)
        return;
    selectY = 7 - selectY;
    if (selected && selectX == selectedPiece.S && selectY == selectedPiece.F){
        resetCellColors();
        selected = false;
        return;
    }
    if (turn == board[selectY][selectX]->getColor()){
        resetCellColors();
        selected = true;
        selectedPiece = {selectY, selectX};
        pair<int, int> *moves = board[selectY][selectX]->moves(board);
        for (int i = 1; i < moves[0].F + 1; i++){
            stats stat = move(selectedPiece, {selectY + moves[i].F, selectX + moves[i].S});
            if (stat.valid){
                display[selectY + moves[i].F][selectX + moves[i].S]->rect.setFillColor(Consts::possibleToMove);
                undo(selectedPiece, {selectY + moves[i].F, selectX + moves[i].S}, stat.piece);
            }
        }
        movement a = backtrack0(selectY, selectX);
        for (auto v: a.pos)
            display[v.F][v.S]->rect.setFillColor(Consts::finallyLose);
        display[selectY][selectX]->rect.setFillColor(Consts::selected);
        movement b = backtrack1(selectY, selectX);
        for (auto v: b.pos)
            display[v.F][v.S]->rect.setFillColor(Consts::finallywin);
        return;
    }
    Color c = display[selectY][selectX]->rect.getFillColor();
    if (selected && (c == Consts::possibleToMove || c == Consts::finallyLose || c == Consts::finallywin)){
        singleMove tmp;
        tmp.checkedCell = checkedCell;
        checkedCell = {-1, -1};
        resetCellColors();
        temp.clear();
        selected = false;
        animate(selectedPiece, {selectY, selectX});
        stats stat = move(selectedPiece, {selectY, selectX});
        tmp.start = selectedPiece;
        tmp.finish = {selectY, selectX};
        tmp.piece = stat.piece;
        if (tmp.piece->getName() != "-")
            board[selectY][selectX]->playKillSound();
        allMoves.PB(tmp);
        if (Mate(turn, getOpponentColor())){
            sound[1].play();
            ended = true;
        }
        if (check(getOpponentColor())){
            for (int i = 0; i < 8; i++)
                for (int j = 0; j < 8; j++)
                    if (board[i][j]->getTitle() == "K" + turn){
                        if (!ended)
                            sound[2].play();
                        display[i][j]->rect.setFillColor(Consts::check);
                        checkedCell = {i, j};
                        return;
                    }
        }
        sound[0].play();
        return;
    }
    
}

//Initializes the board for the first time
void Board::initialize(){
    for (int i = 2; i < 6; i++){
        for (int j = 0; j < 8; j++){
            Null* n = new Null();
            place((Piece*) n, i, j);
        }
    }
    Costume::init<Rook>(this);
    Costume::init<Pawn>(this);
    Costume::init<Knight>(this);
    Costume::init<Queen>(this);
    Costume::init<King>(this);
    Costume::init<Bishop>(this);
    King* white = (King*) board[0][4];
    white->whiteKing = (King*) board[0][4];
    white->blackKing = (King*) board[7][4];
    King* black = (King*) board[7][4];
    black->whiteKing = (King*) board[0][4];
    black->blackKing = (King*) board[7][4];
}

void Board::setCells(){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            Cell* c = new Cell;
            Color temp = (i + j) % 2 == 0 ? Consts::cellColor.F : Consts::cellColor.S;
            c->piece = board[i][j];
            c->rect.setSize(Vector2f(Consts::cellSize, Consts::cellSize));
            c->rect.setFillColor(temp);
            c->rect.setPosition(generateCellPosition(i, j));
            display[i][j] = c;
        }
    sideBarT.loadFromFile("./resources/images/side.png");
    sideBar.setTexture(sideBarT);
    sideBar.setPosition(Vector2f(0, 0));
}

void Board::resetCellColors(){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            Color temp = (i + j) % 2 == 0 ? Consts::cellColor.F : Consts::cellColor.S;
            display[i][j]->rect.setFillColor(temp);
        }
    if (checkedCell.F != -1)
        display[checkedCell.F][checkedCell.S]->rect.setFillColor(Consts::check);
}

Vector2f Board::generateCellPosition(int i, int j){
    i = 7 - i;
    return Vector2f(j * Consts::cellSize + (j - 1) * Consts::cellOffset + Consts::indexRow, i * Consts::cellSize + (i - 1) * Consts::cellOffset);
}


void Board::initText(){
    font.loadFromFile("./resources/fonts/Chilanka-Regular.otf");
    status.setFont(font);
    status.setCharacterSize(25);
    status.setColor(Color::White);
}

void Board::setText(){
    if (ended){
        status.setPosition(855 + Consts::indexRow, 40);
        if (Mate("W", "B"))
            status.setString("Black won!");
        if (Mate("B", "W"))
            status.setString("White won!");
        return;
    }
    status.setPosition(840 + Consts::indexRow, 40);
    string s = (turn == "W" ? "White" : "Black");
    status.setString(s + "'s turn!");
}

void Board::loadSound(){
    buffer[1].loadFromFile("./resources/audios/mate.ogg");
    buffer[0].loadFromFile("./resources/audios/move.ogg");
    buffer[2].loadFromFile("./resources/audios/check.ogg");
    backgroundMusicBuff.loadFromFile("./resources/audios/background.ogg");
    sound[2].setBuffer(buffer[2]);
    sound[0].setBuffer(buffer[0]);
    sound[1].setBuffer(buffer[1]);
    backgroundMusic.setBuffer(backgroundMusicBuff);
    backgroundMusic.setVolume(40);
}

void Board::createButtons(){
    defineButton(&readButton, &readButtonText, Vector2f(160, 60), Vector2f(830 + Consts::indexRow, 100), Consts::buttons, &font, 30, Vector2f(870 + Consts::indexRow, 110), Color::Black, "Read");
    defineButton(&resetButton, &resetButtonText, Vector2f(160, 60), Vector2f(830 + Consts::indexRow, 170), Consts::buttons, &font, 30, Vector2f(865 + Consts::indexRow, 180), Color::Black, "Reset");
    defineButton(&beforeButton, &beforeButtonText, Vector2f(60, 60), Vector2f(830 + Consts::indexRow, 240), Consts::buttons, &font, 70, Vector2f(840 + Consts::indexRow, 220), Color::Black, "<");
    defineButton(&afterButton, &afterButtonText, Vector2f(60, 60), Vector2f(930 + Consts::indexRow, 240), Consts::buttons, &font, 70, Vector2f(935 + Consts::indexRow, 220), Color::Black, ">");
    string x[6] = {"R", "B", "P", "K", "Q", "N"};
    string y[2] = {"W", "B"};
    int i = 300, j = 860;
    for (auto v: x){
        for (auto u: y){
            Texture *a = new Texture();
            a->loadFromFile("./resources/images/" + v + u + ".png");
            Sprite *b = new Sprite();
            b->setTexture(*a);
            b->setPosition(Vector2f(j, i));
            b->setScale(Vector2f(0.9, 0.9));
            a->setSmooth(true);
            globalPiecePosition.insert({v + u, Vector2f(j, i)});
            globalPieces.insert({v + u, b});
            globalTextures.insert({v + u, a});
            j = (j == 860 ? 950 : 860);
        }
        i += 90;
    }
}

void Board::defineButton(RectangleShape *rect, Text *text, Vector2f rectSize, Vector2f rectPos, Color rectColor, Font *font, int charSize, Vector2f textPos, Color textColor, string lable){
    rect->setSize(rectSize);
    rect->setPosition(rectPos);
    rect->setFillColor(rectColor);
    text->setFont(*font);
    text->setCharacterSize(charSize);
    text->setPosition(textPos);
    text->setColor(textColor);
    text->setString(lable);
    text->setStyle(Text::Bold);
}

void Board::animate(pair<int, int> start, pair<int, int> finish){
    int xDiff = generateCellPosition(finish.F, finish.S).x - generateCellPosition(start.F, start.S).x;
    int yDiff = generateCellPosition(finish.F, finish.S).y - generateCellPosition(start.F, start.S).y;
    yDiff /= 10;
    xDiff /= 10;
    float scale = (float) xDiff / yDiff;
    for (int i = 1; i <= 10; i++){
        board[start.F][start.S]->moveSprite(xDiff, yDiff);
        draw();
        window->draw(board[start.F][start.S]->getSprite());
        window->display();
    }
}

void Board::next(){
    if (temp.empty())
        return;
    checkedCell = {-1, -1};
    resetCellColors();
    animate(temp.back().start, temp.back().finish);
    move(temp.back().start, temp.back().finish);
    allMoves.PB(temp.back());
    temp.pop_back();
    sound[0].play();
    if (Mate(turn, getOpponentColor())){
        sound[1].play();
        ended = true;
    }
    if (check(getOpponentColor())){
        for (int i = 0; i < 8; i++)
            for (int j = 0; j < 8; j++)
                if (board[i][j]->getTitle() == "K" + turn){
                    display[i][j]->rect.setFillColor(Consts::check);
                    checkedCell = {i, j};
                    return;
                }
    }
    return;
}

void Board::previous(){
    if (allMoves.empty())
        return;
    ended = false;
    undo(allMoves.back().start, allMoves.back().finish, allMoves.back().piece);
    checkedCell = allMoves.back().checkedCell;
    resetCellColors();
    temp.PB(allMoves.back());
    allMoves.pop_back();
}

void Board::playBackgroundMusic(){
    if (backgroundMusic.getStatus() != Sound::Status::Playing)
        backgroundMusic.play();
}

void Board::changeStatusOfButtons(){
    if (isReading){
        readButtonText.setString("Read");
        beforeButton.setFillColor(Consts::buttons);
        afterButton.setFillColor(Consts::buttons);
        beforeButtonText.setColor(Color::Black);
        afterButtonText.setColor(Color::Black);
        beforeButtonText.setString("<");
        afterButtonText.setString(">");
    }
    else{
        readButtonText.setString("Start");
        beforeButton.setFillColor(Color::Black);
        afterButton.setFillColor(Color::White);
        beforeButtonText.setColor(Color::Cyan);
        afterButtonText.setColor(Color::Cyan);
        beforeButtonText.setString("");
        afterButtonText.setString("*");
    }
}

string Board::dragHandler(Vector2i v){
    if (v.x > 870 && v.y < 300){
        mouseClicked(v);
        return "";
    }
    if (v.x < 860 || v.y > 830)
        return "";
    int selectX = v.x, selectY = v.y;
    selectY -= 300;
    selectY /= 90;
    string key = "";
    if (selectY == 0)
        key = "R";
    else if (selectY == 1)
        key = "B";
    else if (selectY == 2)
        key = "P";
    else if (selectY == 3)
        key = "K";
    else if (selectY == 4)
        key = "Q";
    else if (selectY == 5)
        key = "N";
    if (selectX < 950)
        key += "W";
    else 
        key += "B";
    return key;
}

void Board::moveGlobalSprint(Vector2i v, string piece){
    globalPieces.at(piece)->setPosition(Vector2f(v.x - 40, v.y - 40));
}

void Board::emptyBoard(){
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            Null *n = new Null();
            Piece *temp = board[i][j];
            place((Piece*) n, i, j);
            delete temp;
        }
}

bool Board::drop(Vector2i v, string name){
    string color;
    v.x -= Consts::indexRow;
    if (v.y < 0 || v.x < 0)
        return false;
    int selectX = v.x / 103, selectY = v.y / 103;
    if (selectX > 7 || selectY > 7)
        return false;
    selectY = 7 - selectY;
    Piece *temp = board[selectY][selectX];
    if (name[1] == 'W')
        color = "W";
    else
        color = "B";
    if (name[0] == 'R')
        Costume::placing<Rook>(this, selectY, selectX, color);
    if (name[0] == 'Q')
        Costume::placing<Queen>(this, selectY, selectX, color);
    if (name[0] == 'N')
        Costume::placing<Knight>(this, selectY, selectX, color);
    if (name[0] == 'P')
        Costume::placing<Pawn>(this, selectY, selectX, color);
    if (name[0] == 'B')
        Costume::placing<Bishop>(this, selectY, selectX, color);
    if (name[0] == 'K'){
        if (color == "W")
            if (whiteKingCount == 0){
                Piece* kk = Costume::placing<King>(this, selectY, selectX, color);
                whiteKing = (King*) kk;
                whiteKingCount++;
            }
            else{
                globalPieces.at(name)->setPosition(globalPiecePosition.at(name));
                return true;
            }
        if (color == "B")
            if (blackKingCount == 0){
                Piece* kk = Costume::placing<King>(this, selectY, selectX, color);
                blackKing = (King*) kk;
                blackKingCount++;
            }
            else{
                globalPieces.at(name)->setPosition(globalPiecePosition.at(name));
                return true;
            }
    }
    if (temp->getTitle() == "KW"){
        King* k = new King(100, 100, "W");
        whiteKing = k;
        whiteKingCount = 0;
    }
    if (temp->getTitle() == "KB"){
        King* k = new King(100, 100, "B");
        blackKing = k;
        blackKingCount = 0;
    }
    delete temp;
    globalPieces.at(name)->setPosition(globalPiecePosition.at(name));
}

void Board::loadingScreen(){
    for (int i = 'a'; i <= 'r'; i++){
        string x = string("./resources/images/loadingScreen/") + (char) i + ".jpg";
        t.loadFromFile(x);
        Sprite s;
        s.setTexture(t);
        s.setScale(Vector2f(1, 1));
        s.setPosition(Vector2f(0, 0));
        for (int j = 0; j < 500000000; j++)
            true;
        window->draw(s);
        window->display();
    }
}