#ifndef BOARD_H
#define BOARD_H
#include <wchar.h>
#include <stdbool.h>

typedef enum {
	EMPTY,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
} EPieceType;   

typedef enum {
	WHITE_WIN,
	BLACK_WIN,
	STALEMATE
} EGameState;

typedef enum {
	WHITE,
	BLACK,
	//no color used for empty tiles, which are still technically pieces
	NO_COLOR
} EColor;

typedef struct {
	EColor color;
	EPieceType piece;	
	bool hl;
} Piece;

typedef struct {
	//board[file][rank], [0][0] corresponds to A1, [7][7] to H8  
	Piece *board[8][8];
} Board;

//Test functions
void PrintBoard(Board *board);
void FillBoard(Board *board);
void FillBoardTest(Board *board);
wchar_t GetUnicode(EPieceType, EColor);
#endif
