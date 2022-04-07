build:
	gcc -std=c11 -c main.c
	gcc -std=c11 -c -Wno-return-local-addr game.c
	gcc -std=c11 -c board.c
	#link
	gcc -std=c11 main.o board.o game.o -o a
