#ifndef GAME_H
#define GAME_H
#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

extern const int VALID_MOVE_SIZE;

typedef struct {
	int r0;
	int f0;
	int r1;
	int f1;
} MOVE;

char *Move(int f0, int r0, int f1, int r1, Board *b);
void RawMove(int f0, int r0, int f1, int r1, Board *b);
bool IsValid(int f0, int r0, int f1, int r1, Board *b);
bool IsInCheck(int f0, int r0, int f1, int r1, Board *b);
bool IsMated(int f0, int r0, int f1, int r1, Board *b);
void Capture(int f0, int r0, Board *b);
void Promote(int f0, int r0, Board *b);
void Castling(int f0, int r0, int f1, int r1, Board *b);

void getValidMovesQueen(int, int, Board *, MOVE **);
void getValidMovesRook(int, int, Board *, MOVE **);
void getValidMovesKnight(int, int, Board *, MOVE **);
void getValidMovesBishop(int, int, Board *, MOVE **);
void getValidMovesPawn(int, int, Board *, MOVE **);
void getValidMovesKing(int, int, Board *, MOVE **);

void MoveRandomBlack(Board *b);
void MoveRandomWhite(Board *b);

void SimulateMove(Board *b1, Board *b2, MOVE *m);

#endif
