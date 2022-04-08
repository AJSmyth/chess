#include "game.h"
#include "board.h"
#include <stdio.h>


const int VALID_MOVE_SIZE = 63;

//move the piece at (f0r0) to (f1r1) on the board b
//returns chess algebraic notation of the move if valid
char *Move(int f0, int r0, int f1, int r1, Board *b) {
	if (IsValid(f0, r0, f1, r1, b)) {
		//store the moving piece temporarily
		Piece *p = b->board[f0][r0];
		
		//normal move
		if (b->board[f1][r1]->piece == EMPTY) {
			b->board[f0][r0] = b->board[f1][r1];
			b->board[f1][r1] = p;
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



void Capture(int f0, int r0, Board *b) {
	free(b->board[f0][r0]);
}



//checks if the move from (f0r0) to (f1r1) is valid
bool IsValid(int f0, int r0, int f1, int r1, Board *b) {
	//pointer to array of pointers (stores the address of our array of move pointers)
	//(since this array will be dynamically allocated)
	MOVE *(*valid)[VALID_MOVE_SIZE];

	//get the valid moves array for the corresponding piece
	switch (b->board[f0][r0]->piece) {
		/*
		case QUEEN:
			valid = getValidMovesQueen(f0, r0, b);
			break;
		case ROOK:
			valid = getValidMovesRook(f0, r0, b);
			break;
		case KNIGHT:
			valid = getValidMovesKnight(f0, r0, b);
			break;
		case BISHOP:
			valid = getValidMovesBishop(f0, r0, b);
			break;
		case PAWN:
			valid = getValidMovesPawn(f0, r0, b);
			break;
		case KING:
			valid = getValidMovesKing(f0, r0, b);
			break;
		*/				
		default:
			return true;
	}

	//check the valid moves array for the current move
	for (int i = 0; i < VALID_MOVE_SIZE; ++i) {
	        if (r0 == (*valid)[i]->r0 &&  f0 == (*valid)[i]->f0 && r1 == (*valid[i])->r1 && f1 == (*valid)[i]->f1) {
			return true;
		}
	}

	//if the given move is not found in the valid moves
	return false;
}



MOVE** getValidMovesQueen(int f, int r, Board *b){
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

MOVE **getValidMovesRook(int f0, int r0, Board *b) {
	MOVE *moves[VALID_MOVE_SIZE];
	
	int f = f0, r = r0 + 1, moveCount = 0;
	//check above
	for (; r < 8; ++r) {
		if (!IsInCheck(b->board[f0][r0]->color, b)) {
			if (b->board[f][r]->color != b->board[f0][r0]->color) {
				moves[moveCount] = malloc(sizeof(MOVE));
				moves[moveCount]->f0 = f0;
				moves[moveCount]->r0 = r0;
				moves[moveCount]->f1 = f;
				moves[moveCount]->r1 = r;

				b->board[f][r]->hl = 1;
				if (b->board[f][r]->piece != EMPTY)
					break;
			}
			else { 
				break;
			}
			moveCount++;
		}				
	}

	//check below
	f = f0, r = r0 - 1;	
	for (; r >= 0; --r) {
		if (!IsInCheck(b->board[f0][r0]->color, b)) {
			if (b->board[f][r]->color != b->board[f0][r0]->color) {
				moves[moveCount] = malloc(sizeof(MOVE));
				moves[moveCount]->f0 = f0;
				moves[moveCount]->r0 = r0;
				moves[moveCount]->f1 = f;
				moves[moveCount]->r1 = r;

				b->board[f][r]->hl = 1;
				if (b->board[f][r]->piece != EMPTY)
					break;
			}
			else {
				break;
			}

			moveCount++;
		}				
	}

	//check right
	f = f0 + 1, r = r0;	
	for (; f < 8; ++f) {
		if (!IsInCheck(b->board[f0][r0]->color, b)) {
			if (b->board[f][r]->color != b->board[f0][r0]->color) {
				moves[moveCount] = malloc(sizeof(MOVE));
				moves[moveCount]->f0 = f0;
				moves[moveCount]->r0 = r0;
				moves[moveCount]->f1 = f;
				moves[moveCount]->r1 = r;

				b->board[f][r]->hl = 1;
				if (b->board[f][r]->piece != EMPTY)
					break;
			}
			else break;

			moveCount++;
		}				
	}

	//check left
	f = f0 - 1, r = r0;	
	for (; f >= 0; --f) {
		if (!IsInCheck(b->board[f0][r0]->color, b)) {
			if (b->board[f][r]->color != b->board[f0][r0]->color) {
				moves[moveCount] = malloc(sizeof(MOVE));
				moves[moveCount]->f0 = f0;
				moves[moveCount]->r0 = r0;
				moves[moveCount]->f1 = f;
				moves[moveCount]->r1 = r;

				b->board[f][r]->hl = 1;
				if (b->board[f][r]->piece != EMPTY)
					break;
			}
			else break;

			moveCount++;
		}				
	}
	
	return moves;
}
MOVE **getValidMovesPawn(int f0, int r0, Board *b){
	MOVE *moves[VALID_MOVE_SIZE];
	int f = f0, r = r0, movecount = 0;
	if(b->board[f][r]-> piece = WHITE){
		

	}

}


bool IsInCheck(EColor color, Board *b) {
	return false;
}
