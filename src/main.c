#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "board.h"
#include "game.h"
#include "gui.h"


int main(int argc, char *argv[]) {
	setlocale(LC_ALL, "");	

	GUI *gui = malloc(sizeof(GUI));

	InitGUI(gui);
	DrawMenu(gui);
	bool done = false;

	while (!done) {
		DoGUI(gui);
		if (gui->state == EXITING) done = true;
	}
		
	Cleanup(gui);

	return 0;
}
