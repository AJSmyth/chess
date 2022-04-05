#ifndef BOARD_H
#define BOARD_H
#include <wchar.h>

typedef enum {
	EMPTY = 0,
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
	NO_COLOR
} EColor;

typedef struct {
	EColor color;
	EPieceType piece;	
} Piece;

typedef struct {
	Piece *board[8][8];
} Board;

//Test functions
void PrintBoard(Board *board);
void FillBoard(Board *board);
wchar_t GetUnicode(EPieceType, EColor);
#endif
