#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>

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
    vector<char> symbols;
    vector<char> tapeSymbols;
    string startState;
    char blankSymbol;
    vector<string> finalStates;
    int tapeNum;
    vector<TransitionFunction> delta; 
public:
    TuringMachine(string tmFileName);
    void displayTM();
    void dealInput(string input, bool verbose);
};