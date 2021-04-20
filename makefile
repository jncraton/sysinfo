all: main

main: main.c
	gcc -Wall -Wextra -Werror $< -o $@
	strace ./main
	./main

clean:
	rm -f main
