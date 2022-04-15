#ifndef GUI_H
#define GUI_H
#define _XOPEN_SOURCE_EXTENDED 1
#define NCURSES_WIDECHAR 1 

#include <ncurses.h>
#include <string.h>
#include <stdlib.h>

extern const int MIN_X, MIN_Y;

typedef enum {
	MENU,
	SETTINGS,
	GAME,
} EGUIState;

typedef struct {
	WINDOW *menuArea;
} Menu;

typedef struct {
	Menu *menu;
	EGUIState state;
	int y, x;
} GUI;

bool InitGUI(GUI *g);
void DoGUI(GUI *g);
void DrawMenu(GUI *g);
void mvhwall(int, int, wchar_t, wchar_t, wchar_t, int);
void mvvwall(int, int, wchar_t, int);
#endif
