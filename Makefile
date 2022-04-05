build:
	gcc -c main.c
	gcc -c board.c
	gcc -c game.c
	#link
	gcc main.o board.o game.o -o a

