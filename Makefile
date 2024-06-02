C = gcc
FLAGS = 

program.out: lexer.o
	$(C) $(FLAGS) ./obj/lexer.o -o ./build/program.out

lexer.o: ./src/core/evaluator/lexer/lexer.c 
	$(C) $(FLAGS) -c ./src/core/evaluator/lexer/lexer.c -o ./obj/lexer.o

#parser.o: ./src/core/parser/parser.c \
	$(C) $(FLAGS) -c ./src/core/parser/parser.c -o ./obj/parser.o

#stack.o: ./src/core/data-structures/stack/stack.c \
	$(C) $(FLAGS) -c ./src/core/data-structures/stack/stack.c -o ./obj/stack.o

