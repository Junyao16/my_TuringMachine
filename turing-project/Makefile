turing: turing.o TuringMachine.o
	g++ turing.o TuringMachine.o -o turing
turing.o: turing.cpp
	g++ -c turing.cpp -o turing.o
TuringMachine.o: TuringMachine.cpp
	g++ -c TuringMachine.cpp -o TuringMachine.o




clean: 
	rm -f turing turing.o TuringMachine.o