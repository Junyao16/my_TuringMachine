#include "TuringMachine.h"

TuringMachine::TuringMachine(string tmFileName){
    if(tmFileName.length() <= 3){
        cerr << "turing: \033[31m" << tmFileName << "\033[0m: invalid filename." << endl;
        exit(-1);
    }
    else if(tmFileName.substr(tmFileName.length() - 3, tmFileName.length()) != ".tm"){
        cerr << "turing: \033[31m" << tmFileName << "\033[0m: invalid filename." << endl;
        exit(-1);
    }
    blankSymbol = '\0';
    tapeNum = 0;
    fstream tmFile;
    tmFile.open(tmFileName, ios::in);
    if(!tmFile){
        cerr << "turing: \033[31m" << tmFileName << "\033[0m: No such file or directory." << endl;
        exit(-1);
    }
    else{
        string line;
        int i = 0;
        while(getline(tmFile, line)){
            i++;
            if(line.length() > 5){
                if(line[0] == '#'){
                    if(line[1] == 'Q'){
                        if(states.size() == 0){
                            if(line.length() >= 7){
                                if(line[2] != ' ' || line[3] != '=' || line[4] != ' ' || line[5] != '{' || line[line.length() - 1] != '}'){
                                    cerr << "syntax error" << endl;
                                    cerr << "turing: \033[31mline " << i << "\033[0m: states wrongly defined." << endl;
                                    exit(-1);
                                }
                                for(int j = 6; j < line.length(); j++){
                                    if(line[j] == '}'){
                                        break;
                                    }
                                    else{
                                        string state;
                                        while((line[j] >= '0'&& line[j] <= '9') || (line[j] >= 'a' && line[j] <='z') || (line[j] >= 'A' && line[j] <='Z') || line[j] == '_'){
                                            state += line[j];
                                            j++;
                                        }
                                        if(line[j] != ',' && line[j] != '}'){
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: wrong state symbol character: \'" << line[j] << '\'' << endl;
                                            exit(-1);
                                        }
                                        if(find(states.begin(), states.end(), state) == states.end()){
                                            states.push_back(state);
                                        }
                                        else{
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: state: \'" << state << "\' have been defined twice." << endl;
                                            exit(-1);
                                        }
                                    }
                                    if(line[j] == '}'){
                                        break;
                                    }
                                }

                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: states wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: states have been defined twice." << endl;
                            exit(-1);
                        }
                        // for(int j = 0; j < states.size(); j++){
                        //     cout<<states[j]<<" ";
                        // }
                    }
                    else if(line[1] == 'S'){
                        if(symbols.size() == 0){
                            if(line.length() >= 7){
                                if(line[2] != ' ' || line[3] != '=' || line[4] != ' ' || line[5] != '{' || line[line.length() - 1] != '}'){
                                    cerr << "syntax error" << endl;
                                    cerr << "turing: \033[31mline " << i << "\033[0m: input symbols wrongly defined." << endl;
                                    exit(-1);
                                }
                                for(int j = 6; j < line.length(); j++){
                                    if(line[j] == '}'){
                                        break;
                                    }
                                    else{
                                        char symbol = line[j];
                                        if(line[j] != ' ' && line[j] != ',' && line[j] != ';' && line[j] != '{' && line[j] != '}' && line[j] != '*' && line[j] != '_'){
                                            if(find(symbols.begin(), symbols.end(), symbol) == symbols.end()){
                                                symbols.push_back(symbol);
                                            }
                                            else{
                                                cerr << "syntax error" << endl;
                                                cerr << "turing: \033[31mline " << i << "\033[0m: input symbol: \'" << symbol << "\' have been defined twice." << endl;
                                                exit(-1);
                                            }
                                        }
                                        else if(line[j] != ',' && line[j] != '}'){
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: wrong input symbol: \'" << line[j] << '\'' << endl;
                                            exit(-1);
                                        }
                                    }
                                }
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: input symbols wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: input symbols have been defined twice." << endl;
                            exit(-1);
                        }
                        // for(int j = 0; j < symbols.size(); j++){
                        //     cout<<symbols[j]<<" ";
                        // }
                    }
                    else if(line[1] == 'G'){
                        if(tapeSymbols.size() == 0){
                            if(line.length() >= 7){
                                if(line[2] != ' ' || line[3] != '=' || line[4] != ' ' || line[5] != '{' || line[line.length() - 1] != '}'){
                                    cerr << "syntax error" << endl;
                                    cerr << "turing: \033[31mline " << i << "\033[0m: tape symbols wrongly defined." << endl;
                                    exit(-1);
                                }
                                for(int j = 6; j < line.length(); j++){
                                    if(line[j] == '}'){
                                        break;
                                    }
                                    else{
                                        char tapeSymbol = line[j];
                                        if(line[j] != ' ' && line[j] != ',' && line[j] != ';' && line[j] != '{' && line[j] != '}' && line[j] != '*'){
                                            if(find(tapeSymbols.begin(), tapeSymbols.end(), tapeSymbol) == tapeSymbols.end()){
                                                tapeSymbols.push_back(tapeSymbol);
                                            }
                                            else{
                                                cerr << "syntax error" << endl;
                                                cerr << "turing: \033[31mline " << i << "\033[0m: tape symbol: \'" << tapeSymbol << "\' have been defined twice." << endl;
                                                exit(-1);
                                            }
                                        }
                                        else if(line[j] != ',' && line[j] != '}'){
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: wrong tape symbol: \'" << line[j] << '\'' << endl;
                                            exit(-1);
                                        }
                                    }
                                }
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: tape symbols wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: tape symbols have been defined twice." << endl;
                            exit(-1);
                        }
                        // for(int j = 0; j < tapeSymbols.size(); j++){
                        //     cout<<tapeSymbols[j]<<" ";
                        // }
                    }
                    else if(line[1] == 'q' && line[2] == '0'){
                        if(line[3] != ' ' || line[4] != '=' || line[5] != ' '){
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: start state wrongly defined." << endl;
                            exit(-1);
                        }
                        if(startState.length() == 0){
                            if(line.length() >= 7){
                                startState = line.substr(6, line.length());
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: start state wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: start state have been defined twice." << endl;
                            exit(-1);
                        }
                        // cout<<startState<<endl;
                    }
                    else if(line[1] == 'B'){
                        if(line[2] != ' ' || line[3] != '=' || line[4] != ' '){
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: blank symbol wrongly defined." << endl;
                            exit(-1);
                        }
                        if(blankSymbol == '\0'){
                            if(line.length() == 6){
                                blankSymbol = line[5];
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: blank symbol wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: blank symbol have been defined twice." << endl;
                            exit(-1);
                        }
                        // cout<<blankSymbol<<endl;
                    }
                    else if(line[1] == 'F'){
                        if(line[2] != ' ' || line[3] != '=' || line[4] != ' '){
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: final states wrongly defined." << endl;
                            exit(-1);
                        }
                        if(finalStates.size() == 0){
                            if(line.length() >= 7){
                                if(line[5] != '{' || line[line.length() - 1] != '}'){
                                    cerr << "syntax error" << endl;
                                    cerr << "turing: \033[31mline " << i << "\033[0m: final states wrongly defined." << endl;
                                    exit(-1);
                                }
                                for(int j = 6; j < line.length(); j++){
                                    if(line[j] == '}'){
                                        break;
                                    }
                                    else{
                                        string state;
                                        while((line[j] >= '0'&& line[j] <= '9') || (line[j] >= 'a' && line[j] <='z') || (line[j] >= 'A' && line[j] <='Z') || line[j] == '_'){
                                            state += line[j];
                                            j++;
                                        }
                                        if(line[j] != ',' && line[j] != '}'){
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: wrong state symbol character: \'" << line[j] << '\'' << endl;
                                            exit(-1);
                                        }
                                        if(find(finalStates.begin(), finalStates.end(), state) == finalStates.end()){
                                            finalStates.push_back(state);
                                        }
                                        else{
                                            cerr << "syntax error" << endl;
                                            cerr << "turing: \033[31mline " << i << "\033[0m: final state: \'" << state << "\' have been defined twice." << endl;
                                            exit(-1);
                                        }
                                    }
                                    if(line[j] == '}'){
                                        break;
                                    }
                                }

                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: final states wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: final states have been defined twice." << endl;
                            exit(-1);
                        }
                        // for(int j = 0; j < finalStates.size(); j++){
                        //     cout<<finalStates[j]<<" ";
                        // }
                    }
                    else if(line[1] == 'N'){
                        if(line[2] != ' ' || line[3] != '=' || line[4] != ' '){
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: tape number wrongly defined." << endl;
                            exit(-1);
                        }
                        if(tapeNum == 0){
                            if(line.length() >= 7){
                                string num = line.substr(5, line.length());
                                for(int k = 0; k < num.size(); k++){
                                    if(num[k] >= '0' && num[k] <= '9'){
                                        tapeNum = tapeNum * 10 + num[k] - '0';
                                    }
                                    else if(num[k] != ' '){
                                        cerr << "syntax error" << endl;
                                        cerr << "turing: \033[31mline " << i << "\033[0m: invalid tape number." << endl;
                                        exit(-1);
                                    }
                                }
                            }
                            else{
                                cerr << "syntax error" << endl;
                                cerr << "turing: \033[31mline " << i << "\033[0m: tape number wrongly defined." << endl;
                                exit(-1);
                            }
                        }
                        else{
                            cerr << "syntax error" << endl;
                            cerr << "turing: \033[31mline " << i << "\033[0m: tape number have been defined twice." << endl;
                            exit(-1);
                        }
                        // cout<<startState<<endl;
                    }
                    else{
                        cerr << "syntax error" << endl;
                        cerr << "turing: \033[31mline " << i << "\033[0m: invalid line." << endl;
                        exit(-1);
                    }
                }
                else if(line[0] == ';'){
                    continue;
                }
            }
            else if(line.length() != 0 && line[0] != ';'){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mline " << i << "\033[0m: invalid line." << endl;
                exit(-1);
            }
        }
        if(states.size() == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mstates\033[0m: undefined." << endl;
            exit(-1);
        }
        if(symbols.size() == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31minput symbols\033[0m: undefined." << endl;
            exit(-1);
        }
        if(tapeSymbols.size() == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mtape symbols\033[0m: undefined." << endl;
            exit(-1);
        }
        if(finalStates.size() == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mfinal states\033[0m: undefined." << endl;
            exit(-1);
        }
        if(startState.length() == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mstart state\033[0m: undefined." << endl;
            exit(-1);
        }
        if(blankSymbol == '\0'){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mblank symbol\033[0m: undefined." << endl;
            exit(-1);
        }
        if(blankSymbol != '_'){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mblank symbol\033[0m: wrongly undefined." << endl;
            exit(-1);
        }
        if(tapeNum == 0){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mtape number\033[0m: undefined." << endl;
            exit(-1);
        }
        if(find(states.begin(), states.end(), startState) == states.end()){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mstart states\033[0m: not in all states." << endl;
            exit(-1);
        }
        for(int j = 0; j < finalStates.size(); j++){
            if(find(states.begin(), states.end(), finalStates[j]) == states.end()){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mfinal state: " << finalStates[j] << "\033[0m: not in all states." << endl;
                exit(-1);
            }
        }
        if(find(tapeSymbols.begin(), tapeSymbols.end(), '_') == tapeSymbols.end()){
            cerr << "syntax error" << endl;
            cerr << "turing: \033[31mstart states\033[0m: have no blank symbol." << endl;
            exit(-1);
        }
        for(int j = 0; j < symbols.size(); j++){
            if(find(tapeSymbols.begin(), tapeSymbols.end(), symbols[j]) == tapeSymbols.end()){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31minput symbol: " << symbols[j] << "\033[0m: not in tape symbols." << endl;
                exit(-1);
            }
        }
    }
    tmFile.clear();
    tmFile.close();
    tmFile.open(tmFileName, ios::in);
    if(!tmFile){
        cerr << "turing: \033[31m" << tmFileName << "\033[0m: No such file or directory." << endl;
        exit(-1);
    }
    else{
        string line;
        int i = 0;
        while(getline(tmFile, line)){
            i++;
            if(line.length() == 0){
                continue;
            }
            if(line[0] == '#' || line[0] == ';'){
                continue;
            }
            TransitionFunction tf;
            int j = 0;
            string cState;
            for(; j < line.length(); j++){
                if(line[j] == ' '){
                    break;
                }
                cState += line[j];
            }
            if(find(states.begin(), states.end(), cState) == states.end()){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mline " << i << "\033[0m: invalid current state." << endl;
                exit(-1);
            }
            j++;
            vector<char> oSymbol;
            for(; j < line.length(); j++){
                if(line[j] == ' '){
                    break;
                }
                if(find(tapeSymbols.begin(), tapeSymbols.end(), line[j]) == tapeSymbols.end()){
                    cerr << "syntax error" << endl;
                    cerr << "turing: \033[31mline " << i << "\033[0m: invalid current symbol." << endl;
                    exit(-1);
                }
                oSymbol.push_back(line[j]);
            }
            if(oSymbol.size() != tapeNum){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mline " << i << "\033[0m: invalid current symbols number." << endl;
                exit(-1);
            }
            j++;
            vector<char> nSymbol;
            for(; j < line.length(); j++){
                if(line[j] == ' '){
                    break;
                }
                if(find(tapeSymbols.begin(), tapeSymbols.end(), line[j]) == tapeSymbols.end()){
                    cerr << "syntax error" << endl;
                    cerr << "turing: \033[31mline " << i << "\033[0m: invalid new symbol." << endl;
                    exit(-1);
                }
                nSymbol.push_back(line[j]);
            }
            if(nSymbol.size() != tapeNum){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mline " << i << "\033[0m: invalid new symbols number." << endl;
                exit(-1);
            }
            j++;
            vector<Direction> dir;
            for(; j < line.length(); j++){
                if(line[j] == ' '){
                    break;
                }
                if(line[j] == 'l'){
                    dir.push_back(LEFT);
                }
                else if(line[j] == 'r'){
                    dir.push_back(RIGHT);
                }
                else if(line[j] == '*'){
                    dir.push_back(STILL);
                }
                else{
                    cerr << "syntax error" << endl;
                    cerr << "turing: \033[31mline " << i << "\033[0m: invalid direction." << endl;
                    exit(-1);
                }
            }
            if(dir.size() != tapeNum){
                cerr << "syntax error" << endl;
                    cerr << "turing: \033[31mline " << i << "\033[0m: invalid direction number." << endl;
                    exit(-1);
            }
            j++;
            string nState;
            for(; j < line.length(); j++){
                if(line[j] == ' '){
                    break;
                }
                nState += line[j];
            }
            if(find(states.begin(), states.end(), cState) == states.end()){
                cerr << "syntax error" << endl;
                cerr << "turing: \033[31mline " << i << "\033[0m: invalid new state." << endl;
                exit(-1);
            }
            tf.curState = cState;
            tf.oldSymbol = oSymbol;
            tf.newSymbol = nSymbol;
            tf.direction = dir;
            tf.newState = nState;
            delta.push_back(tf);
        }
    }
    tmFile.clear();
    tmFile.close();
}

void TuringMachine::displayTM(){
    cout << "states: ";
    for(int i = 0; i < states.size(); i++){
        cout << states[i] << ' ';
    }
    cout << endl;
    cout << "symbols: ";
    for(int i = 0; i < symbols.size(); i++){
        cout << symbols[i] << ' ';
    }
    cout << endl;
    cout << "tape symbols: ";
    for(int i = 0; i < tapeSymbols.size(); i++){
        cout << tapeSymbols[i] << ' ';
    }
    cout << endl;
    cout << "start state: ";
    cout << startState;
    cout << endl;
    cout << "blank symbol: ";
    cout << blankSymbol;
    cout << endl;
    cout << "final states: ";
    for(int i = 0; i < finalStates.size(); i++){
        cout << finalStates[i] << ' ';
    }
    cout << endl;
    cout << "tape number: ";
    cout << tapeNum;
    cout << endl;
    cout << "transition functions: " << endl;
    for(int i = 0; i < delta.size(); i++){
        cout << delta[i].curState << ' ';
        for(int j = 0; j < tapeNum; j++){
            cout << delta[i].oldSymbol[j];
        }
        cout << ' ';
        for(int j = 0; j < tapeNum; j++){
            cout << delta[i].newSymbol[j];
        }
        cout << ' ';
        for(int j = 0; j < tapeNum; j++){
            if(delta[i].direction[j] == LEFT){
                cout << 'l';
            }
            if(delta[i].direction[j] == RIGHT){
                cout << 'r';
            }
            if(delta[i].direction[j] == STILL){
                cout << '*';
            }
        }
        cout << ' ';
        cout << delta[i].newState;
        cout << endl;
    }
}

void TuringMachine::dealInput(string input, bool verbose){
    for(int i = 0; i < input.length(); i++){
        if(find(symbols.begin(), symbols.end(), input[i]) == symbols.end()){
            cerr << "illegal input" << endl;
            cerr << "turing: illegal input." << endl;
            exit(-1);
        }
    }
    if(!verbose){
        
    }
}