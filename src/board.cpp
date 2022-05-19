#include "board.h"


Board::Board(){
    initialize();
    turn = "W";
}
Board::Board(bool custom){
    turn = "W";
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            Null* null = new Null();
            place(null, i, j);
        }
}

Board::Board(Piece* board[8][8], string turn){
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
    // cout << "placing " << *piece << endl;
    return temp;
}

Piece* Board::take(pair<int, int> a, pair<int, int> b){
    Null* null = new Null();
    Piece* piece = place(board[a.F][a.S], b.F, b.S);
    place(null, a.F, a.S);
    return piece;
}

movement Board::backtrack0(){
    movement answer;
    for (int j = 0; j < 8; j++)
        for (int i = 0; i < 8; i++){
            if (board[i][j]->getColor() == turn){
                Piece* piece = board[i][j];
                pair<int, int> *moves = piece->moves(board);
                vector<string> temp;
                bool full = 0;
                if (moves[0].F != 0)
                    full = 1;
                for (int k = 1; k < moves[0].F + 1; k++){
                    stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
                    if (!status.valid){
                        if (status.full)
                            full = 0;
                        continue;
                    }
                    if (status.mate || backtrack1().pos.size() != 0)
                        temp.PB(Translate::toString({i, j}, {i + moves[k].F, j + moves[k].S}, piece->getTitle()));
                    else{
                        full = 0;
                    }
                    undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                }
                if (full){
                    string f = "";
                    string s = Translate::toString({i, j}, {0, 0}, piece->getTitle());
                    for (int i = 0; i < 4; i++)
                        f += s[i];
                    answer.pos.PB(f);
                }
                else{
                    for (auto s: temp)
                        answer.pos.PB(s);
                    temp.clear();
                }
            }
        }
    return answer;
}


movement Board::backtrack1(){
    movement answer;
    for (int j = 0; j < 8; j++)
        for (int i = 0; i < 8; i++){
            if (board[i][j]->getColor() == turn){
                Piece *piece = board[i][j];
                pair<int, int> *moves = piece->moves(board);
                vector<string> temp;
                bool full = 0;
                if (moves[0].F != 0)
                    full = 1;
                for (int k = 1; k < moves[0].F + 1; k++){
                    stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
                    if (!status.valid){
                        if (status.full)
                            full = 0;
                        continue;
                    }
                    if (status.mate || backtrack2().mate)
                        temp.PB(Translate::toString({i, j}, {i + moves[k].F, j + moves[k].S}, piece->getTitle()));
                    else{
                        full = 0;
                    }
                    undo({i, j}, {i + moves[k].F, j + moves[k].S}, status.piece);
                }
                if (full){
                    string f = "";
                    string s = Translate::toString({i, j}, {0, 0}, piece->getTitle());
                    for (int i = 0; i < 4; i++)
                        f += s[i];
                    answer.pos.PB(f);
                }
                else{
                    for (auto s: temp)
                        answer.pos.PB(s);
                    temp.clear();
                }
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
            // cout << "backtrack3() ";
            // err2(i);
            // err(j);
            if (board[i][j]->getColor() == turn){
                Piece *piece = board[i][j];
                pair<int, int> *moves = piece->moves(board);
                // cout << "moves of " << *piece << " : " << endl;
                for (int k = 1; k < moves[0].F + 1; k++){
                    // cout << moves[k].F << " " << moves[k].S << endl;
                    stats status = move({i, j}, {i + moves[k].F, j + moves[k].S});
                    if (!status.valid)
                        continue;
                    if (status.mate){
                        // show();
                        // cout << endl;
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
    // cout << "BEFORE:\n";
    // show();
    swap(a, b);
    place(piece, b.F, b.S);
    changeTurn();
    // cout << "AFTER: \n";
    // show();
}


//checks for checkmate situation by turn
//return a boolean
bool Board::Mate(string opponentColor, string turn){
    if (!check(turn))
        return false;
    // string opponentColor = (turn == "W" ? "B" : "W");
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++){
            // cout << "position: " << i << " " << j << endl;
            if (board[i][j]->getColor() == opponentColor){
                Piece* piece = board[i][j];
                if (!checkAfterMove(piece, i, j, opponentColor, turn))
                    return false;
            }
        }
    // show();
    // err2(opponentColor);
    // err(turn);
    // cout << endl;
    return true;
}

bool Board::checkAfterMove(Piece* piece, int p, int q, string opponentColor, string turn){
    pair<int, int>* moves = piece->moves(board);
    // cout << "moves of " << *piece << " in " << piece->getPosition().F << ", " << piece->getPosition().S << ": " << endl;
    for (int i = 1; i < moves[0].F + 1; i++){
        // cout << moves[i].F << " " << moves[i].S << endl;
        if (board[p + moves[i].F][q + moves[i].S]->getColor() == opponentColor)
            continue;
        if (board[p + moves[i].F][q + moves[i].S]->getColor() == "-"){
            swap({p, q}, {p + moves[i].F, q + moves[i].S});
            // cout << '\n';
            // show();
            // cout << '\n';
            if (!check(turn)){
                swap({p, q}, {p + moves[i].F, q + moves[i].S});
                return false;
            }
            swap({p, q}, {p + moves[i].F, q + moves[i].S});
        }
        else{
            // cout << "\n" << turn << board[p + moves[i].F][q + moves[i].S]->getName() << " " << opponentColor << "\n";
            if (!(piece->validTake(moves[i].F, moves[i].S))){
                // cout << "\n" << moves[i].F << " " << moves[i].S << "\n";
                continue;
            }
            Piece* temp = take({p, q}, {p + moves[i].F, q + moves[i].S});
            // cout << '\n';
            // show();
            // cout << '\n';
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
    // err2(turn);
    // err(opponentColor);
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
    if (board[p][q]->getColor() == "W"){
        if (p + 1 < 8 && q + 1 < 8){
            string temp1 = board[p + 1][q + 1]->getName() + board[p + 1][q + 1]->getColor();
            if (temp1 == "PB"){
                // show();
                // cout << "PB\n";
                return true;
            }
        }
        if (p + 1 < 8 && q - 1 > -1){
            string temp2 = board[p + 1][q - 1]->getName() + board[p + 1][q - 1]->getColor();
            if (temp2 == "PB"){
                // show();
                // cout << "PB\n";
                return true;
            }
        }
    }
    else{
        if (p - 1 > -1 && q + 1 < 8){
            string temp1 = board[p - 1][q + 1]->getName() + board[p - 1][q + 1]->getColor();
            if (temp1 == "PW"){
                // show();
                // cout << "PW\n";
                return true;
            }
        }
        if (p - 1 > -1 && q - 1 > -1){
            string temp2 = board[p - 1][q - 1]->getName() + board[p - 1][q - 1]->getColor();
            if (temp2 == "PW"){
                // show();
                // cout << "PW\n";
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
                // show();
                // cout << "N\n";
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
                            // show();
                            // cout << tempName + board[p + i * a][q + i * b]->getColor() << endl;
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
            // cout << "BEFORE: \n";
            // show();
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
        // cout << "BEFORE: \n";
        // show();
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
    Piece *tmp;
    King *white, *black;
    for (int i = 7; i > -1; i--){
        for (int j = 0; j < 8; j++){
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
    while(window->isOpen()){
        Event event;
        while(window->pollEvent(event)){
            if (event.type == Event::Closed){
                window->close();
            }
        }
        window->clear(Color::Black);
        draw();
        window->display();
    }
}

void Board::draw(){};

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

