C = gcc
FLAGS = 

program.out: lexer.o parser.o
	$(C) $(FLAGS) ./obj/lexer.o ./obj/parser.o -o ./build/program.out

lexer.o: ./src/core/lexer/lexer.c 
	$(C) $(FLAGS) -c -ggdb3 ./src/core/lexer/lexer.c -o ./obj/lexer.o

parser.o: ./src/core/parser/parser.c 
	$(C) $(FLAGS) -c -ggdb3 ./src/core/parser/parser.c -o ./obj/parser.o


