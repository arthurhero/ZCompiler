ZCompiler : ZCompiler.o
	g++ -Wall ZCompiler.o -o ZCompiler

ZCompiler.o : ZCompiler.cpp
	g++ -c -Wall ZCompiler.cpp

clean :
	rm *.o ZCompiler

test :
