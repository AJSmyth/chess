#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ncurses.h>
#include <string.h>
#include "board.h"
#include "game.h"
#include "gui.h"


int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE,"");	
	Board *chessBoard = malloc(sizeof(Board));
	//Board *chessBoardCopy = malloc(sizeof(Board));
	FillBoard(chessBoard);
	EGUIState gui = MENU;

	//PrintBoard(chessBoard);

	bool done = false;
	/*
	 while (!done) {
		printf("Select a piece to move in the form \"FR FR\" (e.g. A2 A3): ");
		char s0[3], s1[3];
		scanf("%2s %2s", s0, s1);
		//MOVE *moves[63];
		#ifdef TEST
		printf("Valid: %d | Move: %s %s", IsValid(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard), s0, s1);
		#else
		Move(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard);
		//CopyBoard(chessBoard, chessBoardCopy);
		#endif

		PrintBoard(chessBoard);
	}	
	return 0;
	*/


	return 0;
}
