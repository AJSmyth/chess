#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "board.h"
#include "game.h"


int main(int argc, char *argv[]) {
	setlocale(LC_CTYPE,"");	
	Board *chessBoard = malloc(sizeof(Board));
	//Board *chessBoardCopy = malloc(sizeof(Board));
	int a;
	printf("Select 1 for White and 2 for Black and 3 for Free Play: ");
	scanf("%d",&a);
	FillBoard(chessBoard);
	PrintBoard(chessBoard);

	//If side chosen is White
	if (a == 1)
	{
		bool done = false;
		while (!done){
		printf("Select a piece to move in the form \"FR FR\" (e.g. A2 A3): ");
		char s0[3], s1[3];
		char *MoveCheck;
		scanf("%2s %2s", s0, s1);

		if (chessBoard->board[s0[0] - 65][s0[1] - 49]->color == BLACK)
		{
			printf("Invalid move! Choose a White piece!\n");
			continue;
		}
        
		Move(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard);

		//Implement a Move check function which checks if the 
		//previous move by the player was valid (To Be Done)
		//if (MoveCheck == 0)
		//{
		//	continue;
		//}

		MoveRandomBlack(chessBoard);
		PrintBoard(chessBoard);

		}
	}

	//If side chosen is Black
	if (a == 2)
	{
		bool done = false;
		while (!done){
		printf("Select a piece to move in the form \"FR FR\" (e.g. A2 A3): ");
		char s0[3], s1[3];
		char *MoveCheck;
		scanf("%2s %2s", s0, s1);

		if (chessBoard->board[s0[0] - 65][s0[1] - 49]->color == WHITE)
		{
			printf("Invalid move! Choose a Black piece!\n");
			continue;
		}

		Move(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard);

		//Implement a Move check function which checks if the 
		//previous move by the player was valid (To Be Done)
		//if (MoveCheck == 0)
		//{
		//	continue;
		//}

		MoveRandomWhite(chessBoard);
		PrintBoard(chessBoard);

		}
	}

	if (a == 3)
	{
		bool done = false;
		while (!done) 
		{
			printf("Select a piece to move in the form \"FR FR\" (e.g. A2 A3): ");
			char s0[3], s1[3];
			scanf("%2s %2s", s0, s1);
			//MOVE *moves[63];
			#ifdef TEST
			printf("Valid: %d | Move: %s %s", IsValid(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard), s0, s1);
			#else
			Move(s0[0] - 65, s0[1] - 49, s1[0] - 65, s1[1] - 49, chessBoard);
			//CopyBoard(chessBoard, chessBoardCopy);
			#endif

			PrintBoard(chessBoard);
		}	
	}




	return 0;
}
