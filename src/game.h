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
/*
typedef struct{
	TREE_EL *root;
} TREE;

typedef struct {
	TREE_EL *parent;
	Board *value;
	TREE_EL_LIST *children;
}TREE_EL;

typedef struct{
	TREE_EL_LIST_MEM *first;
}TREE_EL_LIST;

typedef struct{
	TREE_EL_LIST *list;
	TREE_EL_LIST_MEM *next;
}TREE_EL_LIST_MEM;
*/

typedef struct LLElem LLElem;

struct LLElem{
	void *data;
	LLElem *next;
};

typedef struct{
	LLElem *first;
	LLElem *last;
}LL;


char *Move(int f0, int r0, int f1, int r1, Board *b);
void RawMove(int f0, int r0, int f1, int r1, Board *b);
bool IsValid(int f0, int r0, int f1, int r1, Board *b);
bool IsInCheck(int f0, int r0, int f1, int r1, Board *b);
bool IsMated(Board *b, EColor color);
void Capture(int f, int r, Board *b);
void Promote(int f0, int r0, Board *b);
void Castling(int f0, int r0, int f1, int r1, Board *b);

LL *getValidMovesQueen(int, int, Board *);
LL *getValidMovesRook(int, int, Board *);
LL *getValidMovesKnight(int, int, Board *);
LL *getValidMovesBishop(int, int, Board *);
LL *getValidMovesPawn(int, int, Board *);
LL *getValidMovesKing(int, int, Board *);

LL *getValidMoves(Board *, EColor);

void MoveRandomBlack(Board *b);
void MoveRandomWhite(Board *b);

void SimulateMove(Board *b1, Board *b2, MOVE *m);
void CAN(int, int, int, int, Board *);

//void GenerateTree(Board *source, TREE *out, int depth);
int EvaluateBoard(Board *b);

MOVE *IdealMove(Board *b, EColor player);

void Append(LL *list, void *data);
void DeleteList(LL *list);
#endif
