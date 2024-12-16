all: main

main: main.c 
	gcc -Wall -g main.c -o main -lcurl

clean:
	rm -f main
