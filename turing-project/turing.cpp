#include <iostream>
#include <stdio.h>
#include <string>
#include "TuringMachine.h"

using namespace std;

bool verbose = 0;
string tmFileName;
string tmInput;

int judge_arg(int argc, char* argv[]);

int main(int argc, char* argv[]) {
    judge_arg(argc, argv);
    TuringMachine tm(tmFileName);
    return 0;
}

// deal with arguments
int judge_arg(int argc, char* argv[]){
    int flag = 0;
    string arg;
    for(int i = 1; i < argc; i++){
        arg = argv[i];
        if(arg[0] == '-'){
            if(arg == "-h" || arg == "--help"){
                cout << "usage: turing [-v|--verbose] [-h|--help] <tm> <input>" << endl;
                exit(0);
            }
            else if(arg == "-v" || arg == "--verbose"){
                verbose = 1;
            }
            else{
                cerr << "turing: unknown option argument \"" << arg << "\"" <<endl;
                cerr << "Use \"turing --help\" for a complete list of options." << endl;
                exit(-1);
            }
        }
        else{
            if(tmFileName.length() == 0){
                tmFileName = arg;
            }
            else if(tmInput.length() == 0){
                tmInput = arg;
            }
            else{
                cerr << "turing: unknown command \"" << arg << "\"" <<endl;
                cerr << "Use \"turing --help\" for a complete list of options." << endl;
                exit(-1);
            }
        }
    }
}