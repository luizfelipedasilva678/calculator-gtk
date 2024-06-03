C = gcc
FLAGS = 

program.out: evaluator.o lexer.o parser.o
	$(C) $(FLAGS) ./obj/evaluator.o ./obj/lexer.o ./obj/parser.o -o ./build/program.out

evaluator.o: ./src/core/evaluator/evaluator.c
	$(C) $(FLAGS) -c -ggdb3 ./src/core/evaluator/evaluator.c -o ./obj/evaluator.o

lexer.o: ./src/core/lexer/lexer.c  
	$(C) $(FLAGS) -c -ggdb3 ./src/core/lexer/lexer.c -o ./obj/lexer.o

parser.o: ./src/core/parser/parser.c  
	$(C) $(FLAGS) -c -ggdb3 ./src/core/parser/parser.c -o ./obj/parser.o


