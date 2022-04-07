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
bool IsInCheck(EColor color, Board *b);
bool IsMated(EColor color, Board *b);
void Capture(int f0, int r0, Board *b);
void Promote(int f0, int r0, Board *b);

MOVE** getValidMovesQueen(int f, int r, Board *b);
MOVE **getValidMovesRook(int f, int r, Board *b);

#endif
