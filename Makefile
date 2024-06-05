C = gcc
FLAGS = -Wall -Werror -pedantic-errors 


program.out: evaluator.o lexer.o parser.o
	$(C) $(FLAGS) $$(pkg-config --cflags gtk4) ./src/ui/calculator.c ./obj/evaluator.o ./obj/lexer.o ./obj/parser.o -o  ./build/program.out -lm $$(pkg-config --libs gtk4)

evaluator.o: ./src/core/evaluator/evaluator.c
	$(C) $(FLAGS) -c ./src/core/evaluator/evaluator.c -o ./obj/evaluator.o

lexer.o: ./src/core/lexer/lexer.c  
	$(C) $(FLAGS) -c ./src/core/lexer/lexer.c -o ./obj/lexer.o

parser.o: ./src/core/parser/parser.c  
	$(C) $(FLAGS) -c ./src/core/parser/parser.c -o ./obj/parser.o


