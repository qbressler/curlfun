all: main

main: program.c 
	gcc -Wall -g program.c -o program -lcurl

clean:
	rm -f program
