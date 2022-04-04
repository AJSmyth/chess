#include "board.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE,"");	
	Board *chessBoard = malloc(sizeof(Board));
	FillBoard(chessBoard);
	PrintBoard(chessBoard);
}

void PrintBoard(Board *board) {
	printf("\n\n╔═══╤═══╤═══╤═══╤═══╤═══╤═══╤═══╗\n");
	for (int rank = 7; rank >= 0; --rank) {
		printf("║");
		for (int file = 0; file < 8; ++file) {
			printf(" %lc ", GetUnicode(board->board[file][rank]->piece, board->board[file][rank]->color));
			if (file != 7) printf("│");
		}
		printf("║\n");

		if (rank != 0)
			printf("╟───┼───┼───┼───┼───┼───┼───┼───╢\n");
		else 
			printf("╚═══╧═══╧═══╧═══╧═══╧═══╧═══╧═══╝\n");
	}
}

//board[file][rank] (0,0)->A1 
void FillBoard(Board *chessBoard) {
	for (int file = 0; file < 8; ++file) {
		for (int rank = 0; rank < 8; ++rank) {
			chessBoard->board[file][rank] = malloc(sizeof(Piece));
		}
		//fill empty tiles from A3 to H6
		for (int rank = 1; rank < 5; ++rank) {
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
				return 0x265F;
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
