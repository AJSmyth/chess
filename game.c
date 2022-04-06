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
		        b->board[f0][r0] = malloc(sizeof(Piece));
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

MOVE* getValidMovesQueen(int f, int r, Board *b){
	MOVE *moves[63];
	int curr_move = 0;
	//check vertical line up
	for(int i = r+1; i < 8; i++){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = i;
		moves[curr_move]->f1 = f;
		b->board[f][i]->hl = 1;
		if(!(b->board[f][i]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check vertical line down
	for(int i = r-1; i >= 0; i--){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = i;
		moves[curr_move]->f1 = f;
		b->board[f][i]->hl = 1;
		if(!(b->board[f][i]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check horizontal line right
	for(int i = f+1; i < 8; i++){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = r;
		moves[curr_move]->f1 = i;
		b->board[i][r]->hl = 1;
		if(!(b->board[i][r]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check horizontal line left
	for(int i = f-1; i >= 0; i--){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = r;
		moves[curr_move]->f1 = i;
		b->board[i][r]->hl = 1;
		if(!(b->board[i][r]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check diagonal top right
	for(int i = f+1, j=r+1; i<8 && j<8; i++,j++){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = j;
		moves[curr_move]->f1 = i;
		b->board[i][j]->hl = 1;
		if(!(b->board[i][j]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check diagonal bottom right
	for(int i = f+1, j=r-1; i<8 && j>=0; i++,j--){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = j;
		moves[curr_move]->f1 = i;
		b->board[i][j]->hl = 1;
		if(!(b->board[i][j]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check diagonal bottom left
	for(int i = f-1, j=r-1; i>=0 && j>=0; i--,j--){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = j;
		moves[curr_move]->f1 = i;
		b->board[i][j]->hl = 1;
		if(!(b->board[i][j]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	//check diagonal top left
	for(int i = f-1, j=r+1; i>=0 && j<8; i--,j++){
		moves[curr_move] = malloc(sizeof(MOVE));
		moves[curr_move]->r0 = r;
		moves[curr_move]->f0 = f;
		moves[curr_move]->r1 = j;
		moves[curr_move]->f1 = i;
		b->board[i][j]->hl = 1;
		if(!(b->board[i][j]->piece == EMPTY)){
			break;
		}
		curr_move++;
	}
	return moves;
}

void Capture(int f0, int r0, Board *b) {
	free(b->board[f0][r0]);
}
