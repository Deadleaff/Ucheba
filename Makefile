prog: main.o algorithm.o 
	gcc main.o algorithm.o -o prog -lm
main.o: main.c header.h
	gcc main.c -c -Wall -Wextra -Werror
algorithm.o: algorithm.c header.h
	gcc algorithm.c -c -Wall -Wextra -Werror
clean:
	rm -f a main.o algorithm.o

prog_debug: main_debug.o algorithm_debug.o 
	gcc -g -O0 main_debug.o algorithm_debug.o -o prog_debug -lm
main_debug.o: main.c header.h
	gcc -g -O0 main.c -c -Wall -Wextra -Werror -o main_debug.o
algorithm_debug.o: algorithm.c header.h
	gcc -g -O0 algorithm.c -c -Wall -Wextra -Werror -o algorithm_debug.o
