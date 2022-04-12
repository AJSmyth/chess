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
bool IsValid(int f0, int r0, int f1, int r1, Board *b);
bool IsInCheck(int f0, int r0, int f1, int r1, Board *b);
bool IsMated(EColor color, Board *b);
void Capture(int f0, int r0, Board *b);
void Promote(int f0, int r0, Board *b);

void getValidMovesQueen(int, int, Board *, MOVE **);
MOVE **getValidMovesRook(int, int, Board *);
MOVE **getValidMovesKnight(int, int, Board *);
MOVE **getValidMovesBishop(int, int, Board *);
MOVE **getValidMovesPawn(int, int, Board *);
MOVE **getValidMovesKing(int, int, Board *);

#endif
