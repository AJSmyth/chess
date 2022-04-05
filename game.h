#ifndef GAME_H
#define GAME_H
#include "board.h"
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

char *Move(int f0, int r0, int f1, int r1, Board *b);
bool IsValid(int f0, int r0, int f1, int r1, Board *b);
bool IsInCheck(EColor color, Board *b);
bool IsMated(EColor color, Board *b);
void Capture(int f0, int r0, Board *b);
void Promote(int f0, int r0, Board *b);
char PieceTypeToChar(EPieceType);

#endif
