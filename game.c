#include "board.h"
#include "game.h"
#include <stdio.h>

//returns chess algebraic notation of move if valid
char *Move(int f0, int r0, int f1, int r1, Board *b) {
	printf("Move Got input: %d%d, %d%d", f0, r0, f1, r1);
	if (IsValid(f0, r0, f1, r1, b)) {
		Piece *p = b->board[f0][r0];
		printf("VALID MOVE");
		//normal move
		if (b->board[f1][r1]->piece == EMPTY) {
			b->board[f0][r0] = b->board[f1][r1];
			b->board[f1][r1] = p;
			printf("EMPTYPIECE::");
		}

		//implement promotion
		//implement en passant
		
		//capturing move
		else {
			Capture(f1, r1, b);
			b->board[f1][r1] = p;
		        b->board[f0][r0] = malloc(sizeof(Board));
			b->board[f0][r0]->piece = EMPTY;
			b->board[f0][r0]->color = NO_COLOR;
		}
	}
	return "";
}

bool IsValid(int f0, int r0, int f1, int r1, Board *b) {
	//todo: implement real check
	return true;
}

void Capture(int f0, int r0, Board *b) {
	free(b->board[f0][r0]);
}
