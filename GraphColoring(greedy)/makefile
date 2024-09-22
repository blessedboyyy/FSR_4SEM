all : ans

ans : parser.o solver.o main.o
	g++ parser.o solver.o main.o -o main

main.o: parser.h solver.h
parser.o : parser.h
solver.o : solver.h

clean:
	@rm -rf ans *.o