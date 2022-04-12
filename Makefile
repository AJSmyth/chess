build:
	gcc -std=c11 -c main.c
	gcc -std=c11 -c -Wno-return-local-addr game.c
	gcc -std=c11 -c board.c
	gcc -std=c11 -c gui.c
	#link
	gcc -std=c11 main.o board.o game.o gui.o -o a -lncurses
