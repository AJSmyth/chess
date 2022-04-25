#include "game.h"
#include "board.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <ncurses.h>

const int VALID_MOVE_SIZE = 63;

//move the piece at (f0r0) to (f1r1) on the board b
//returns chess algebraic notation of the move if valid
char *Move(int f0, int r0, int f1, int r1, Board *b) {
	if (IsValid(f0, r0, f1, r1, b)) {
		//-------- Update Misc. Board Data --------	
		//To count the total number of moves of each piece
		b->board[f0][r0]->counter++;
		
		if(b->currentPlayerTurn == BLACK) {
			b->currentPlayerTurn = WHITE;
		}else{
			b->currentPlayerTurn = BLACK;
		}

		//---------- Move the Piece ----------------
		//store the moving piece temporarily
		Piece *p = b->board[f0][r0];

		//White Pawn En Passant
		if (b->board[f1][r1-1]->piece == PAWN && (b->board[f0][r0]->color != b->board[f1][r1-1]->color) && b->board[f0][r0]->color == WHITE ) {
		 if(r0 == 4 && b->board[f1][r1-1]->counter == 1){
			 b->board[f0][r0]->isCapturing = true; //so that CAN know that it is capturing
			printf("%d\n", b->board[f0][r0]->isCapturing);
			CAN(f0, r0, f1, r1, b);
			printf("CAPTURING");
			Capture(f1, r1-1, b);
			b->board[f1][r1] = p;
			b->board[f0][r0] = malloc(sizeof(Piece));
			b->board[f0][r0]->piece = EMPTY;
			b->board[f0][r0]->color = NO_COLOR;
			b->board[f1][r1-1] = malloc(sizeof(Piece));
			b->board[f1][r1-1]->piece = EMPTY;
			b->board[f1][r1-1]->color = NO_COLOR;
		 }
		}
		//Black Pawn En Passant
		if (b->board[f1][r1+1]->piece == PAWN && (b->board[f0][r0]->color != b->board[f1][r1+1]->color) && b->board[f0][r0]->color == BLACK ) {
		 if(r0 == 3 && b->board[f1][r1+1]->counter == 1){
			 b->board[f0][r0]->isCapturing = true; //so that CAN know that it is capturing
			printf("%d\n", b->board[f0][r0]->isCapturing);
			CAN(f0, r0, f1, r1, b);

			printf("CAPTURING");
			Capture(f1, r1 + 1, b);
			b->board[f1][r1] = p;
			b->board[f0][r0] = malloc(sizeof(Piece));
			b->board[f0][r0]->piece = EMPTY;
			b->board[f0][r0]->color = NO_COLOR;
			b->board[f1][r1+1] = malloc(sizeof(Piece));
			b->board[f1][r1+1]->piece = EMPTY;
			b->board[f1][r1+1]->color = NO_COLOR;
		 }
		}

		//normal move
		if (b->board[f1][r1]->piece == EMPTY) {
			//CAN(f0, r0, f1, r1, b);
			b->board[f0][r0] = b->board[f1][r1];
			b->board[f1][r1] = p;
			Castling (f0, r0, f1, r1, b);
		}
		
		//capturing move (prevent capturing king)
		else if (b->board[f1][r1]->piece != KING) {
			b->board[f0][r0]->isCapturing = true; //so that CAN know that it is capturing
			//printf("%d\n", b->board[f0][r0]->isCapturing);
			//CAN(f0, r0, f1, r1, b);

			//printf("CAPTURING");
			Capture(f1, r1, b);
			b->board[f1][r1] = p;
			b->board[f0][r0] = malloc(sizeof(Piece));
			b->board[f0][r0]->piece = EMPTY;
			b->board[f0][r0]->color = NO_COLOR;
		}
		/*
		if (b->board[f0][r0]->piece == PAWN) printf("dOMOSF");
		
		//promotion (PAWN HAS BEEN MOVED)	
		if (b->board[f1][r1]->piece == PAWN) {
			if ((r1 == 7 && b->board[f1][r1]->color == WHITE) || (r1 == 0 && b->board[f1][r1]->color == BLACK)) {	
				char promoteTo;
				printf("Please choose a piece to promote your pawn to: \nQ:Queen\nN:Knight\nB:Bishop\nR:Rook\nPiece:");
				scanf(" %c", &promoteTo);
				switch(promoteTo){
					  case 'B':
					 b->board[f1][r1]->isPromoted = true;
					 b->board[f1][r1]->piece = BISHOP;
					 break;

					  case 'N':
					 b->board[f1][r1]->isPromoted = true;
					 b->board[f1][r1]->piece = KNIGHT;
					 break;

					  case 'R':
					 b->board[f1][r1]->isPromoted = true;
					 b->board[f1][r1]->piece = ROOK;
					 break;
					 default: 
					 b->board[f1][r1]->isPromoted = true;
					 b->board[f1][r1]->piece = QUEEN;
				}
			}
		}
		*/
		mvprintw(1,1, "             ");

	}else{
		mvprintw(1,1,"INVALID MOVE!");
		//printf("Invalid move!\n");
	}
	return "";
}


//move the specified piece to the captured array
void Capture(int f, int r, Board *b) {
	int offset = (b->board[f][r]->color == WHITE) ? 0 : 2;

	b->cap[offset][b->nCapW] = b->board[f][r];
	b->board[f][r] = NULL;
}



//checks if the move from (f0r0) to (f1r1) is valid
bool IsValid(int f0, int r0, int f1, int r1, Board *b) {
	//pointer to array of pointers (stores the address of our array of move pointers)
	//(since this array will be dynamically allocated)
	LL *moves;
	
	//get the valid moves array for the corresponding piece
	switch (b->board[f0][r0]->piece) {
		case QUEEN:
			moves = getValidMovesQueen(f0, r0, b);
			break;
		case ROOK:
			moves = getValidMovesRook(f0, r0, b);
			break;
		case KNIGHT:
			moves = getValidMovesKnight(f0, r0, b);
			break;
		case BISHOP:
			moves = getValidMovesBishop(f0, r0, b);
			break;
		case PAWN:
			moves = getValidMovesPawn(f0, r0, b);
			break;
		case KING:
			moves = getValidMovesKing(f0, r0, b);
			break;
		default:
			return false;
	}
	LLElem *curr = moves->first;
	while(curr){
		MOVE *currmove = (MOVE *)(curr->data);
		if(currmove->r1 == r1 && currmove->f1 == f1 && !IsInCheck(f0,r0,f1,r1,b)){
			DeleteList(moves);
			return true;
		}
		curr = curr->next;
	}
	//if the given move is not found in the valid moves
	DeleteList(moves);
	return false;
}

void MoveRandomBlack(Board *b)
{
	srand(time(NULL)); 
	int a = rand() % 8; 
	int e = rand() % 8; 
	int c = rand() % 8; 
	int d = rand() % 8; 
	int count = 0;
	while (1)
	{	
		a = rand() % 8; //Select a Random file for initial move
		e = rand() % 8; //Select a Random rank for initial move

		if(b->board[a][e]->color == BLACK)
		{
			for(count = 0; count <= 200; count++) 
			//Repeat the loop 200 times to find a valid move
			//200 is chosen randomly in order to avoid pieces which do not have any valid moves
			//If there are no valid moves in 200 tries, the loop breaks
			{
				c = rand() % 8; //Select a Random file for final move
				d = rand() % 8; //Select a Random rank for final move
				if (IsValid(a,e,c,d,b))
				{
					Move(a,e,c,d,b);
					return;
				}
			}
		}
	}
}

void MoveRandomWhite(Board *b)
{
	srand(time(NULL)); 
	int a = rand() % 8; 
	int e = rand() % 8; 
	int c = rand() % 8; 
	int d = rand() % 8; 
	int count = 0;
	while (1)
	{	
		a = rand() % 8; //Select a Random file for initial move
		e = rand() % 8; //Select a Random rank for initial move

		if(b->board[a][e]->color == WHITE)
		{
			for(count = 0; count <= 200; count++) 
			//Repeat the loop 200 times to find a valid move
			//200 is chosen randomly in order to avoid pieces which do not have any valid moves
			//If there are no valid moves in 200 tries, the loop breaks
			{
				c = rand() % 8; //Select a Random file for final move
				d = rand() % 8; //Select a Random rank for final move
				if (IsValid(a,e,c,d,b))
				{
					Move(a,e,c,d,b);
					return;
				}
			}
		}
	}
}



LL *getValidMovesKnight(int f0, int r0, Board *b) {
	//TODO: WE NEED TO TEST THIS
	//MOVE *moves[63];
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;
	int f, r;
	//check two spaces left and one space down
	f = f0 - 2;
	r = r0 - 1;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check one space left and two spaces down
	f = f0 - 1;
	r = r0 - 2;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check one space right and two spaces up
	f = f0 + 1;
	r = r0 + 2;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check two spaces right and one space up
	f = f0 + 2;
	r = r0 + 1;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check two spaces left and one space up
	f = f0 - 2;
	r = r0 + 1;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check one space left and two spaces up
	f = f0 - 1;
	r = r0 + 2;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check one space right and two spaces down
	f = f0 + 1;
	r = r0 - 2;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}
	//check two spaces right and one space down
	f = f0 + 2;
	r = r0 - 1;
	if(f >= 0 && f < 8 && r >=0 && r < 8){
		if(b->board[f0][r0]->color != b->board[f][r]->color){ //if the spot the piece is moving to is not the color moving to
		 MOVE *curr = malloc(sizeof(MOVE));
		 curr -> f0 = f0;
		 curr -> r0 = r0;
		 curr -> f1 = f;
		 curr -> r1 = r;
		 Append(out, curr);
	   }
	}

	return out;
}

LL *getValidMovesQueen(int f, int r, Board *b){
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;

	//check vertical line up
	for(int i = r+1; i < 8; i++){
		//b->board[f][i]->hl = 1;
		if(b->board[f][i]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = i;
			curr->f1 = f;
			Append(out, curr);
			if(b->board[f][i]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check vertical line down
	for(int i = r-1; i >= 0; i--){
		//b->board[f][i]->hl = 1;
		if(b->board[f][i]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = i;
			curr->f1 = f;
			Append(out, curr);
			if(b->board[f][i]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check horizontal line right
	for(int i = f+1; i < 8; i++){
		//b->board[i][r]->hl = 1;
		if(b->board[i][r]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = i;
			Append(out, curr);
			if(b->board[i][r]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check horizontal line left
	for(int i = f-1; i >= 0; i--){
		//b->board[i][r]->hl = 1;
		if(b->board[i][r]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = i;
			Append(out, curr);
			if(b->board[i][r]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check diagonal top right
	for(int i = f+1, j=r+1; i<8 && j<8; i++,j++){
		//b->board[i][j]->hl = 1;
		if(b->board[i][j]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			if(b->board[i][j]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check diagonal bottom right
	for (int i = f+1, j= r-1; i < 8 && j>=0; i++, j--){
		if (b->board[f][r]->color != b->board[i][j]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
			if (b->board[i][j]->piece != EMPTY){
				break;
			}
		}

		else break;
	}
	//check diagonal bottom left
	for(int i = f-1, j=r-1; i>=0 && j>=0; i--,j--){
		//b->board[i][j]->hl = 1;
		if(b->board[i][j]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			if(b->board[i][j]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}
	//check diagonal top left
	for(int i = f-1, j=r+1; i>=0 && j<8; i--,j++){
		//b->board[i][j]->hl = 1;
		if(b->board[i][j]->color != b->board[f][r]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r;
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			if(b->board[i][j]->piece != EMPTY){
				break;
			}
		}else{
			break;
		}
	}

	return out;
}


LL *getValidMovesRook(int f0, int r0, Board *b) {
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;

	int f = f0, r = r0 + 1;
	
	//check above
	for (; r < 8; ++r) {
		//if (!IsInCheck(f0, r0, f, r, b)) {
		if (b->board[f][r]->color != b->board[f0][r0]->color) {
			MOVE *curr = malloc(sizeof(MOVE));
			curr->f0 = f0;
			curr->r0 = r0;
			curr->f1 = f;
			curr->r1 = r;
			Append(out, curr);
			if (b->board[f][r]->piece != EMPTY) {
				break;
			}
		}
		else { 
			break;
		}			
	}

	//check below
	f = f0, r = r0 - 1;	
	for (; r >= 0; --r) {
		//if (!IsInCheck(f0, r0, f, r, b)) {
		if (b->board[f][r]->color != b->board[f0][r0]->color) {
			MOVE *curr = malloc(sizeof(MOVE));
			curr->f0 = f0;
			curr->r0 = r0;
			curr->f1 = f;
			curr->r1 = r;
			Append(out, curr);
			//b->board[f][r]->hl = 1;
			if (b->board[f][r]->piece != EMPTY) {
				break;
			}
		}
		else {
			break;
		}
	}

	//check right
	f = f0 + 1, r = r0;	
	for (; f < 8; ++f) {
		//if (!IsInCheck(f0, r0, f, r, b)) {
		if (b->board[f][r]->color != b->board[f0][r0]->color) {
			MOVE *curr = malloc(sizeof(MOVE));
			curr->f0 = f0;
			curr->r0 = r0;
			curr->f1 = f;
			curr->r1 = r;
			Append(out, curr);
			//b->board[f][r]->hl = 1;
			if (b->board[f][r]->piece != EMPTY) {
				break;
			}
		}
		else break;			
	}

	//check left
	f = f0 - 1, r = r0;	
	for (; f >= 0; --f) {
		//if (!IsInCheck(f0, r0, f, r, b)) {
		if (b->board[f][r]->color != b->board[f0][r0]->color) {
			MOVE *curr = malloc(sizeof(MOVE));
			curr->f0 = f0;
			curr->r0 = r0;
			curr->f1 = f;
			curr->r1 = r;
			Append(out, curr);
			//b->board[f][r]->hl = 1;
			if (b->board[f][r]->piece != EMPTY) {
				break;
			}
		}
		else break;			
	}

	return out;
	//return moves;
}

//SEGMENTATION FAULT NEEDS MORE DEBUGGING
LL *getValidMovesBishop(int f, int r, Board *b){
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;

	//check diagonal top right
	for (int i = f+1, j= r+1; i < 8 && j < 8; i++, j++){
		if (b->board[f][r]->color != b->board[i][j]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
			if (b->board[i][j]->piece != EMPTY){
				break;
			}
		}

		else break;

	}
	//check diagonal bottom right
	for (int i = f+1, j= r-1; i < 8 && j>=0; i++, j--){
		if (b->board[f][r]->color != b->board[i][j]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
			if (b->board[i][j]->piece != EMPTY){
				break;
			}
		}

		else break;
	}
	//check diagonal bottom left
	for (int i = f-1, j= r-1; i >= 0 && j >= 0; i--, j--){
		if (b->board[f][r]->color != b->board[i][j]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
			if (b->board[i][j]->piece != EMPTY){
				break;
			}
		}
		else break;
	}
	//check diagonal top left
	for (int i = f-1, j= r+1; i>=0 && j < 8; i--, j++){
		if (b->board[f][r]->color != b->board[i][j]->color){
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = j;
			curr->f1 = i;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
			if (b->board[i][j]->piece != EMPTY){
				break;
			}
		}
		else break;
	}

	return out;
}

LL *getValidMovesKing(int f,int r, Board *b){
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;
		
	//Castling using White Rook on the Right Side
	if (b->board[7][0]->piece == ROOK && b->board[7][0]->color == WHITE && b->board[f][r]->counter == 0 && f == 4 && r == 0 && b->board[f][r]->color == WHITE && b->board[f+1][r]->piece == EMPTY && b->board[f+2][r]->piece == EMPTY && b->board[6][0]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 0;
		curr->f1 = 6;
		Append(out, curr);
	} 

	//Castling using White Rook on the Left Side
	if (b->board[0][0]->piece == ROOK && b->board[0][0]->color == WHITE && b->board[f][r]->counter == 0 && f == 4 && r == 0 && b->board[f][r]->color == WHITE && b->board[f-1][r]->piece == EMPTY && b->board[f-2][r]->piece == EMPTY && b->board[f-3][r]->piece == EMPTY  && b->board[2][0]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 0;
		curr->f1 = 2;
		Append(out, curr);
	}	
	
	//Castling using Black Rook on the Right Side
	if (b->board[7][7]->piece == ROOK && b->board[7][7]->color == BLACK && b->board[f][r]->counter == 0 && f == 4 && r == 7 && b->board[f][r]->color == BLACK && b->board[f+1][r]->piece == EMPTY && b->board[f+2][r]->piece == EMPTY  && b->board[6][7]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 7;
		curr->f1 = 6;
		Append(out, curr);
	}

	//Castling using Black Rook on the Left Side
	if (b->board[0][7]->piece == ROOK && b->board[0][7]->color == BLACK && b->board[f][r]->counter == 0 && f == 4 && r == 7 && b->board[f][r]->color == BLACK && b->board[f-1][r]->piece == EMPTY && b->board[f-2][r]->piece == EMPTY && b->board[f-3][r]->piece == EMPTY  && b->board[2][7]->counter == 0)
	{
		MOVE *curr = malloc(sizeof(MOVE));
		curr->r0 = r; 
		curr->f0 = f;
		curr->r1 = 7; 
		curr->f1 = 2;
		Append(out, curr);
	}

	//Check 1 space above
	if (r+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space below
		
	if (r-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the left

	if (f-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f-1][r]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the right
	
	if (f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the Upper Right
	
	if (r+1 <= 7 && f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space to the Upper Left
	
	if (r+1 <= 7 && f-1 >=0)
	{
		if (b->board[f][r]->color != b->board[f-1][r+1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r+1;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}

	//Check 1 space to the Lower Right
	
	if (r-1 >= 0 && f+1 <= 7)
	{
		if (b->board[f][r]->color != b->board[f+1][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f+1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	
	//Check 1 space to the Lower Left
	
	if (r-1 >= 0 && f-1 >= 0)
	{
		if (b->board[f][r]->color != b->board[f-1][r-1]->color)
		{ 
			MOVE *curr = malloc(sizeof(MOVE));
			curr->r0 = r; 
			curr->f0 = f;
			curr->r1 = r-1;
			curr->f1 = f-1;
			Append(out, curr);
			//b->board[i][j]->hl = 1;
		}
	}
	return out;
}

LL *getValidMovesPawn(int f0, int r0, Board *b){
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;
	//FOR WHITE PAWN
	//check to see if white pawn can move forward 2 spaces
	if(b-> board[f0][r0]->color == WHITE){
		int f = f0, r = r0 + 2, moveCount = 0;
		if(r0 == 1 && b->board[f0][r0+1]->piece == EMPTY && b->board[f0][r0+2]->piece == EMPTY){
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//check to see if white pawn can move forward a space
		f = f0, r = r0 + 1;
		if(r < 8 && b->board[f0][r0+1]->piece == EMPTY){
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//check to see if white pawn can capture right diagonally
		f = f0+1, r = r0 +1; //right diagonal
		//if(!IsInCheck(f0, r0, f, r, b)){//check to see if move to be made will put King in check
		if(f < 8 && r < 8 && b->board[f][r]->color == BLACK){//piece should not be white and not empty to capture
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//}

		//EN PASSANT for WHITE PAWN
		f = f0+1, r = r0+1;
		if (f < 8 && r < 8){
			if(b->board[f0+1][r0]->piece == PAWN && b->board[f0+1][r0]->color == BLACK){
		   		if(r0 == 4 && b->board[f0+1][r0]->counter == 1){
			 	 MOVE *curr = malloc(sizeof(MOVE));
			 	 curr -> f0 = f0;
			 	 curr -> r0 = r0;
			 	 curr -> f1 = f;
			 	 curr -> r1 = r;
			 	 Append(out, curr);
		   		}
		    }
		}
		f = f0-1, r = r0+1;
		if (f >= 0 && r < 8){
			if(b->board[f0-1][r0]->piece == PAWN && b->board[f0-1][r0]->color == BLACK){
		   		if(r0 == 4 && b->board[f0-1][r0]->counter == 1){
			 	MOVE *curr = malloc(sizeof(MOVE));
			 	curr -> f0 = f0;
			 	curr -> r0 = r0;
			 	curr -> f1 = f;
			 	curr -> r1 = r;
			 	Append(out, curr);
		   	    }
		    }
		}
		//check to see if white pawn can capture left diagonally
		f = f0 - 1, r = r0 + 1; //left diagonal
		//if(!IsInCheck(f0, r0, f, r, b)){ //check to see if move to be made will put King in check
		if(f >= 0 && r < 8 && b->board[f][r]->color == BLACK){ //piece should not be white and not empty to capture
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);		
		}
		//}
		//PROMOTION FOR WHITE PAWN
	}
	//FOR BLACK PAWN
	if(b-> board[f0][r0]->color == BLACK){
		//check to see if black pawn can move forward two spaces 
		int f = f0, r = r0 - 2, moveCount = 0;
		if(r0 == 6 &&  b->board[f0][r0-1]->piece == EMPTY && b->board[f0][r0-2]->piece == EMPTY){
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//check to see if black pawn can move forward a space
		f = f0, r = r0 - 1;
		if(r >= 0 && b->board[f0][r0-1]->piece == EMPTY){
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//check to see if black pawn can capture right diagonally
		f = f0 - 1, r = r0 - 1; //right diagonal
		if(f >= 0 && r >= 0 && b->board[f][r]->color == WHITE){//piece should not be white and not empty to capture
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
		//check to see if black pawn can capture left diagonally
		f = f0 + 1, r = r0 - 1; //left diagonal
		//check to see if move to be made will put King in check
		if(f < 8 && r >= 0 && b->board[f][r]->color == WHITE){ //piece should not be white and not empty to capture
			MOVE *curr = malloc(sizeof(MOVE));
			curr -> f0 = f0;
			curr -> r0 = r0;
			curr -> f1 = f;
			curr -> r1 = r;
			Append(out, curr);	
		}
				//EN PASSANT for BLACK PAWN
		f = f0-1, r = r0-1;
		if (f >= 0 && r >= 0){
		    if(b->board[f0-1][r0]->piece == PAWN && b->board[f0-1][r0]->color == WHITE){

             if(r0 == 3 && b->board[f0-1][r0]->counter == 1){
			  MOVE *curr = malloc(sizeof(MOVE));
			  curr -> f0 = f0;
			  curr -> r0 = r0;
			  curr -> f1 = f;
			  curr -> r1 = r;
			  Append(out, curr);
		      }
		    }
		}
		f = f0+1, r = r0-1;
		if (f < 8 && r >= 0){
		    if(b->board[f0+1][r0]->piece == PAWN && b->board[f0+1][r0]->color == WHITE){
		      if(r0 == 3 && b->board[f0+1][r0]->counter == 1){
			   MOVE *curr = malloc(sizeof(MOVE));
			   curr -> f0 = f0;
			   curr -> r0 = r0;
			   curr -> f1 = f;
			   curr -> r1 = r;
			   Append(out, curr);
		      }
		   }
		}
	}
	return out;
}

bool IsInCheck(int f0, int r0, int f1, int r1, Board *b) {
	LL *moves;
	Board *b2 = malloc(sizeof(Board));
	MOVE *m = malloc(sizeof(MOVE));
	m->f0 = f0;
	m->r0 = r0;
	m->f1 = f1;
	m->r1 = r1;
	SimulateMove(b, b2, m);
	free(m);
	for(int f = 0; f < 8; f++){
		for(int r = 0; r < 8; r++){
			if(b2->board[f][r]->piece != EMPTY){
				switch (b2->board[f][r]->piece) {
				case QUEEN:
					moves = getValidMovesQueen(f, r, b2);
					break;
				case ROOK:
					moves = getValidMovesRook(f, r, b2);
					break;
				case KNIGHT:
					moves = getValidMovesKnight(f, r, b2);
					break;
				case BISHOP:
					moves = getValidMovesBishop(f, r, b2);
					break;
				case PAWN:
					moves = getValidMovesPawn(f, r, b2);
					break;
				case KING:
					getValidMovesKing(f, r, b2);
					break;
				default:
					break;
				}

				LLElem *curr = moves->first;
				while(curr){
					MOVE *currmove = (MOVE *)(curr->data);
					if(b2->board[currmove->f1][currmove->r1]->piece == KING && b2->board[currmove->f1][currmove->r1]->color == b2->board[f1][r1]->color){
						DeleteBoard(b2);
						DeleteList(moves);
						return true;
					}
					curr = curr->next;
				}
			}
		}
	}
	DeleteBoard(b2);
	DeleteList(moves);
	return false;
}

LL *getValidMoves(Board * board, EColor player){
	LL *sublist;
	LL *out = malloc(sizeof(LL));
	out->first = NULL;
	out->last = NULL;

	for(int f = 0; f < 8; f++){
		for(int r = 0; r < 8; r++){
			if(board->board[f][r]->piece != EMPTY){
				switch (board->board[f][r]->piece) {
				case QUEEN:
					sublist = getValidMovesQueen(f, r, board);
					break;
				case ROOK:
					sublist = getValidMovesRook(f, r, board);
					break;
				case KNIGHT:
					sublist = getValidMovesKnight(f, r, board);
					break;
				case BISHOP:
					sublist = getValidMovesBishop(f, r, board);
					break;
				case PAWN:
					sublist = getValidMovesPawn(f, r, board);
					break;
				case KING:
					sublist = getValidMovesKing(f, r, board);
					break;
				default:
					break;
				}

				LLElem *curr = sublist->first;
				while(curr){
					MOVE *currmove = (MOVE *)(curr->data);
					if(board->board[currmove->f0][currmove->r0]->color == player && !IsInCheck(currmove->f0,currmove->r0,currmove->f1,currmove->r1, board)){
						Append(out, currmove);
					}
					curr = curr->next;
				}
			}
		}
	}

	return out;
}

bool IsMated(Board *b, EColor color) {
	LL *m = getValidMoves(b, color);
	bool mated = (m->first == NULL);
	DeleteList(m);
	return mated;
}

void Castling(int f0, int r0, int f1, int r1, Board *b)
{
	if (f1 == 6 && r1 == 0 && f0 == 4 && r0 == 0)
	{
		Piece *x = b->board[7][0];
		
		b->board[7][0] = b->board[5][0];
		b->board[5][0] = x;
	}

	if (f1 == 2 && r1 == 0 && f0 == 4 && r0 == 0)
	{
		Piece *x = b->board[0][0];
		
		b->board[0][0] = b->board[3][0];
		b->board[3][0] = x;
	}

	if (f1 == 6 && r1 == 7 && f0 == 4 && r0 == 7)
	{
		Piece *x = b->board[7][7];
		
		b->board[7][7] = b->board[5][7];
		b->board[5][7] = x;
	}

	if (f1 == 2 && r1 == 7 && f0 == 4 && r0 == 7)
	{
		Piece *x = b->board[0][7];
		
		b->board[0][7] = b->board[3][7];
		b->board[3][7] = x;
	}

}

void SimulateMove(Board *b1, Board *b2, MOVE *m){
	CopyBoard(b1, b2);
	RawMove(m->f0, m->r0, m->f1, m->r1, b2);
}

void RawMove(int f0, int r0, int f1, int r1, Board *b){
	if(f0<8 && f0>=0 && r0<8 && r0>=0 && f1<8 && f1>=0 && r1<8 && r1>=0){
		Piece *p = b->board[f0][r0];
		if (b->board[f1][r1]->piece == EMPTY) {
			b->board[f0][r0] = b->board[f1][r1];
			b->board[f1][r1] = p;
			//Castling (f0, r0, f1, r1, b);
		}else {
			Capture(f1, r1, b);
			b->board[f1][r1] = p;
			b->board[f0][r0] = malloc(sizeof(Piece));
			b->board[f0][r0]->piece = EMPTY;
			b->board[f0][r0]->color = NO_COLOR;
		}
	}
}

int EvaluateBoard(Board *b){
	int value = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(b->board[i][j]->piece != EMPTY){
				switch (b->board[i][j]->piece) {
				case QUEEN:
					if(b->board[i][j]->color == WHITE){
						value+=9;
					}else{
						value-=9;
					}
					break;
				case ROOK:
					if(b->board[i][j]->color == WHITE){
						value+=5;
					}else{
						value-=5;
					}
					break;
				case KNIGHT:
					if(b->board[i][j]->color == WHITE){
						value+=3;
					}else{
						value-=3;
					}
					break;
				case BISHOP:
					if(b->board[i][j]->color == WHITE){
						value+=3;
					}else{
						value-=3;
					}
					break;
				case PAWN:
					if(b->board[i][j]->color == WHITE){
						value+=1;
					}else{
						value-=1;
					}
					break;
				default:
					break;
				}
			}
		}
	}
	return value;
}
/*
MOVE *IdealMove(Board *b, EColor player){
	LL *moves;
	int score = EvaluateBoard(b);

	MOVE * best = malloc(sizeof(MOVE));

	Board * b2 = malloc(sizeof(Board));
	
	DeleteBoard(b2);
	return best;
}
void GenerateTree(Board *source, TREE *out, int depth){
	MOVE * valid[VALID_MOVE_SIZE];

	TREE_EL *rootelement = malloc(sizeof(TREE_EL));
	TREE->root = rootelement;
	rootelement->parent = NULL;
	rootelement->value = source;

	
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(source->board[i][j]->piece != EMPTY){
				switch (source->board[i][j]->piece) {
				case QUEEN:
					getValidMovesQueen(i, j, source, valid);
					break;
				case ROOK:
					getValidMovesRook(i, j, source, valid);
					break;
				case KNIGHT:
					getValidMovesKnight(i, j, source, valid);
					break;
				case BISHOP:
					getValidMovesBishop(i, j, source, valid);
					break;
				case PAWN:
					getValidMovesPawn(i, j, source, valid);
					break;
				case KING:
					getValidMovesKing(f, r, b2, valid);
					break;
				default:
					break;
				}
			}
		}
	}
}
*/

MOVE *IdealMove(Board *b, EColor color) {
	srand(time(NULL)); 

	LL *m = getValidMoves(b, color);
	int size = GetListSize(m);
	int n = rand() % size; 

	//iterate through n elements of the moves list
	LLElem *curr = m->first;
	for (; n >= 0; --n) {
		curr = curr->next;	
	}

	//deep copy move to allow freeing
	MOVE *move = malloc(sizeof(MOVE));
	move->f0 = ((MOVE *)curr->data)->f0;
	move->r0 = ((MOVE *)curr->data)->r0;
	move->f1 = ((MOVE *)curr->data)->f1;
	move->r1 = ((MOVE *)curr->data)->r1;

	DeleteList(m);
	return move;
}




void CAN(int f0, int r0, int f1, int r1, Board *b){

	switch(b->board[f0][r0]->piece){
		case QUEEN:
			if (b->board[f0][r0]->isPromoted == true){

				if (b->board[f0][r0]->isCapturing ==  true){
					printf("x%c%d=Q", 65+f1, r1+1);
				}else {
					printf("%c%d=Q", 65+f1, r1+1);
					b->board[f0][r0]->isCapturing =  false;
				}
			} else if (b->board[f0][r0]->isCapturing ==  true){
				printf("Qx%c%d", 65+f1, r1+1);
				b->board[f0][r0]->isCapturing =  false;

			} else {
				printf("Q%c%d", 65+f1, r1+1);
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}

			printf(" ");
			break;
		
		case ROOK:
			if (b->board[f0][r0]->isPromoted == true){

				if (b->board[f0][r0]->isCapturing ==  true){
					printf("x%c%d=R", 65+f1, r1+1);
				}else {
					printf("%c%d=R", 65+f1, r1+1);
					b->board[f0][r0]->isCapturing =  false;
				}
			} else if (b->board[f0][r0]->isCapturing ==  true){
				printf("Rx%c%d", 65+f1, r1+1);
				b->board[f0][r0]->isCapturing =  false;

			}else{
				printf("R%c%d", 65+f1, r1+1);
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}

			printf(" ");

			break;
		
		case KNIGHT:
			if (b->board[f0][r0]->isPromoted == true){

				if (b->board[f0][r0]->isCapturing ==  true){
					printf("x%c%d=N", 65+f1, r1+1);
				}else {
					printf("%c%d=N", 65+f1, r1+1);
					b->board[f0][r0]->isCapturing =  false;
				}

			} else if (b->board[f0][r0]->isCapturing ==  true){
				printf("Nx%c%d", 65+f1, r1+1);
				b->board[f0][r0]->isCapturing =  false;

			} else{
				printf("N%c%d", 65+f1, r1+1);
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}


			printf(" ");

			break;
		case BISHOP:
			if (b->board[f0][r0]->isPromoted == true){

				if (b->board[f0][r0]->isCapturing ==  true){
					printf("x%c%d=B", 65+f1, r1+1);
				}else {
					printf("%c%d=B", 65+f1, r1+1);
					b->board[f0][r0]->isCapturing =  false;
				}

			} else if (b->board[f0][r0]->isCapturing ==  true){

				if(IsInCheck(f0,r0,f1,r1,b)){
					printf("Bx%c%d+", 65+f1, r1+1);	
				}else {
					printf("Bx%c%d", 65+f1, r1+1);
					b->board[f0][r0]->isCapturing =  false;
				}

			} else{
				printf("B%c%d", 65+f1, r1+1);	
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}
			break;


			printf(" ");

		case PAWN:

			if (b->board[f0][r0]->isCapturing ==  true){
				printf("ex%c%d", 65+f1, r1+1);
				b->board[f0][r0]->isCapturing =  false;

			} else{
				//printf("f1: %c, r1: %d", 65+f1, r1+1);
				printf("%c%d", 65+f1, r1+1);
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}

			printf(" ");
			break;
		case KING:
		
			if (b->board[f0][r0]->isCapturing ==  true){
				printf("Kx%c%d", 65+f1, r1+1);
				b->board[f0][r0]->isCapturing =  false;
			} else {
				printf("K%c%d", 65+f1, r1+1);
			}

			if(IsInCheck(f0,r0,f1,r1,b)){
				printf("+");
			}

			printf(" ");

			break;
		default:
			printf("");
	}
}

void Append(LL *list, void *data){
	LLElem *new = malloc(sizeof(LLElem));
	new->data = data;
	new->next = NULL;

	if(list->first){
		list->last->next = new;
		list->last = new;
	}else{
		list->first = new;
		list->last = new;
	}
}

void DeleteList(LL *list){
	LLElem *curr = list->first;
	LLElem *next;
	while(curr){
		free(curr->data);
		next = curr->next;
		free(curr);
		curr = next;
	}
	free(list);
	list = NULL;
}

int GetListSize(LL *list) {
	int i = 0;
	LLElem *curr = list->first;

	while (curr->next) {
		i++;
		curr = curr->next;
	}

	return i;
}
