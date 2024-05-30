C = gcc
FLAGS = -Wall -Werror -pedantic-errors

program.out: parser.o stack.o
	$(C) $(FLAGS) ./obj/parser.o ./obj/stack.o -o ./build/program.out

parser.o: ./src/core/parser/parser.c
	$(C) $(FLAGS) -c ./src/core/parser/parser.c -o ./obj/parser.o

stack.o: ./src/core/data-structures/stack/stack.c
	$(C) $(FLAGS) -c ./src/core/data-structures/stack/stack.c -o ./obj/stack.o
