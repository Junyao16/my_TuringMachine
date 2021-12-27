#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

enum Direction{
    LEFT,
    RIGHT,
    STILL
};

struct TransitionFunction{
    string curState;
    vector<char> oldSymbol;
    vector<char> newSymbol;
    vector<Direction> direction;
    string newState;
};

class TuringMachine{
private:
    vector<string> states;
    vector<char> symbol;
    vector<char> tapeSymbol;
    string q0;
    char blank;
    vector<string> finalStates;
    int tapeNum;
    vector<TransitionFunction> delta; 
public:
    TuringMachine(string tmFileName);
};