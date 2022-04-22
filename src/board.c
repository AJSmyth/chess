#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>



void PrintBoard(Board *b) {
	#ifndef TEST	
	system("clear");
	#endif
	printf("\n  ╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n");
	for (int rank = 7; rank >= 0; --rank) {
		printf("%d ║", rank + 1);
		for (int file = 0; file < 8; ++file) {
			if(!b->board[file][rank]->hl){
				printf(" %lc ", GetUnicode(b->board[file][rank]->piece, b->board[file][rank]->color));
			}else{
				printf("<%lc>", GetUnicode(b->board[file][rank]->piece, b->board[file][rank]->color));
			}
			if (file != 7) printf("│");
		}
		printf("║\n");

		if (rank != 0)
			printf("  ╟───┼───┼───┼───┼───┼───┼───┼───╢\n");
		else { 
			printf("  ╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n");
			printf("    A   B   C   D   E   F   G   H\n");
		}
	}

	//clear highlighting for next turn
	for (int r = 0; r < 8; ++r) {
		for (int f = 0; f < 8; ++f) {
			b->board[f][r]->hl = 0;
		}
	}
}



void FillBoard(Board *chessBoard) {
	for (int file = 0; file < 8; ++file) {
		for (int rank = 0; rank < 8; ++rank) {
			chessBoard->board[file][rank] = malloc(sizeof(Piece));
			chessBoard->board[file][rank]->hl = 0;
			chessBoard->board[file][rank]->counter = 0;
		}
		//fill empty tiles from A3 to H6
		for (int rank = 1; rank <= 5; ++rank) {
			chessBoard->board[file][rank]->piece = EMPTY;
			chessBoard->board[file][rank]->color = NO_COLOR;
		}

		//set colors
		chessBoard->board[file][0]->color = WHITE;
		chessBoard->board[file][1]->color = WHITE;
		chessBoard->board[file][6]->color = BLACK;
		chessBoard->board[file][7]->color = BLACK;
	
		//setup pawns quickly	
		chessBoard->board[file][1]->piece = PAWN;
		chessBoard->board[file][6]->piece = PAWN;
	}

	//set up other pieces
	chessBoard->board[0][0]->piece = ROOK;
	chessBoard->board[1][0]->piece = KNIGHT;
	chessBoard->board[2][0]->piece = BISHOP;
	chessBoard->board[3][0]->piece = QUEEN;
	chessBoard->board[4][0]->piece = KING;
	chessBoard->board[5][0]->piece = BISHOP;
	chessBoard->board[6][0]->piece = KNIGHT;
	chessBoard->board[7][0]->piece = ROOK;
		
	chessBoard->board[0][7]->piece = ROOK;
	chessBoard->board[1][7]->piece = KNIGHT;
	chessBoard->board[2][7]->piece = BISHOP;
	chessBoard->board[3][7]->piece = QUEEN;
	chessBoard->board[4][7]->piece = KING;
	chessBoard->board[5][7]->piece = BISHOP;
	chessBoard->board[6][7]->piece = KNIGHT;
	chessBoard->board[7][7]->piece = ROOK;
}



//this function is here to setup the board in however way needed for testing
void FillBoardTest(Board *chessBoard) {
	for (int file = 0; file < 8; ++file) {
		for (int rank = 0; rank < 8; ++rank) {
			chessBoard->board[file][rank] = malloc(sizeof(Piece));
			chessBoard->board[file][rank]->hl = 0;
			chessBoard->board[file][rank]->piece = EMPTY;
			chessBoard->board[file][rank]->color = NO_COLOR;
		}
	}
	chessBoard->board[4][4]->piece = QUEEN;
	chessBoard->board[4][4]->color = WHITE;
}



//return the corresponding chess piece character (e.g. white pawn ♙ = 0x2659) given the color and piece type
//note: unicode characters must be stored in the wchar_t type due to their larger size
wchar_t GetUnicode(EPieceType piece, EColor color) {
	if (color == WHITE) {
		switch (piece) {
			case PAWN:
				return 0x2659;
			case ROOK:
			       return 0x2656;
			case KNIGHT:
			       return 0x2658;
			case BISHOP:
			       return 0x2657;
			case QUEEN:
			      return 0x2655;
			case KING:
			      return 0x2654;
			default:
			      return ' ';
		}
	}
	else {
		switch (piece) {
			case PAWN:
				return 0x2659; //0x265F;
			case ROOK:
			       return 0x265C;
			case KNIGHT:
			       return 0x265E;
			case BISHOP:
			       return 0x265D;
			case QUEEN:
			      return 0x265B;
			case KING:
			      return 0x265A;
			default:
			      return ' ';
		}
	}
}

void CopyBoard(Board *b1, Board *b2){
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			Piece *clone = malloc(sizeof(Piece));
			clone->piece = b1->board[i][j]->piece;
			clone->color = b1->board[i][j]->color;
			free(b2->board[i][j]);
			b2->board[i][j] = clone;
		}
	}
}

void DeleteBoard(Board *b){
	for(int i = 0; i<8; i++){
		for(int j = 0; j<8; j++){
			if(b->board[i][j]){
				free(b->board[i][j]);
			}
		}
	}
	free(b);
	b = NULL;
}
