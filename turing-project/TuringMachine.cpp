#include "TuringMachine.h"

TuringMachine::TuringMachine(string tmFileName){
    fstream tmFile;
    tmFile.open(tmFileName, ios::in);
    if(!tmFile){
        cerr << "turing: \033[31m" << tmFileName << "\033[0m: No such file or directory." << endl;
        exit(-1);
    }
}