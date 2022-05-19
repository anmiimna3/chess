#include "translate.h"

Translate::Translate(){}

pair<pair<int, int>, pair<int, int>> Translate::toNormal(string input){
    pair<int, int> a = {input[0] - 97, input[1] - 49};
    pair<int, int> b = {input[4] - 97, input[5] - 49};
    // pair<int, int> c = {b.F - a.F, b.S - a.S};
    return {a, b};
}

string Translate::toString(pair<int, int> a, pair<int, int> b, string name){
    name = (char) (a.F + 49) + name;
    name = (char) (a.S + 97) + name;
    name += (char) (b.S + 97);
    name += (char) (b.F + 49);
    return name; 
}  
