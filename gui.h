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
	int x0, x1;
	int y0, y1;
} Box;

typedef struct {
	Box bound;
	int value;
	char *text;
} MenuOption;

typedef struct {
	MenuOption **options;
	int selected;
	char *text;
	int labelX, labelY;
	size_t size;
} MenuSetting;

typedef struct {
	//MenuSetting represents [text | MenuOption[0] | ... | MenuOption[size - 1]]
	MenuSetting *gamemode;
	MenuSetting *difficulty;

	size_t nSet;
	MenuSetting **settings;
	Box exit;
} Menu;

typedef struct {
	Menu *menu;
	EGUIState state;
	int y, x;
} GUI;

bool IsInBox(int y, int x, Box b);
void SetBox(MenuSetting *, int, int, int);
bool InitGUI(GUI *g);
void DoGUI(GUI *g);
void DrawMenu(GUI *g);
void HandleMouse(GUI *g, MEVENT e);


void mvhwall(int, int, wchar_t, wchar_t, wchar_t, int);
void mvvwall(int, int, wchar_t, int);
#endif
