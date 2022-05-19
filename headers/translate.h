#include <iostream>

#define F first
#define S second

using namespace std;

class Translate{
    public:
        Translate();

        static pair<pair<int, int>, pair<int, int>> toNormal(string input);

        static string toString(pair<int, int> a, pair<int, int> b, string name);
};