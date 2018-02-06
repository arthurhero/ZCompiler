ZCompiler : ZCompiler.o boolean.o ifstate.o integer.o loperator.o oper.o paren.o
	g++ -Wall ZCompiler.o boolean.o ifstate.o integer.o loperator.o oper.o paren.o -o ZCompiler

ZCompiler.o : ZCompiler.cpp token.h boolean.h ifstate.h integer.h loperator.h oper.h paren.h
	g++ -c -Wall ZCompiler.cpp

boolean.o : boolean.cpp boolean.h token.h
	g++ -c -Wall boolean.cpp

ifstate.o : ifstate.cpp ifstate.h token.h boolean.h
	g++ -c -Wall ifstate.cpp

integer.o : integer.cpp integer.h token.h
	g++ -c -Wall integer.cpp

loperator.o : loperator.cpp loperator.h token.h integer.h boolean.h
	g++ -c -Wall loperator.cpp

oper.o : oper.cpp oper.h token.h integer.h
	g++ -c -Wall oper.cpp

paren.o : paren.cpp paren.h token.h
	g++ -c -Wall paren.cpp

clean :
	rm *.o ZCompiler

test :
