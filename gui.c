#include "gui.h"

const int MIN_X = 0, MIN_Y = 0;

//start ncurses mode, returns false if window size is smaller than chess board
bool InitGUI(GUI *g) {
	g->state = MENU; 

	initscr();
	curs_set(0);
	getmaxyx(stdscr, g->y, g->x);
	wattrset(stdscr, A_NORMAL);

	if (g->y < MIN_Y || g->x < MIN_X) return false;
	else return true;

	//set up mouse event
	mousemask(BUTTON1_CLICKED, NULL);
}

//to be called in main game loop, handle the GUI operation
void DoGUI(GUI *g) {
	//handle mouse input	
	
	//handle gui drawing
	switch (g->state) {
		case MENU:
			DrawMenu(g);
		break;
	}
}

//draws and handles the menu 
void DrawMenu(GUI *g) {
	char *title = "QUEEN'S CHESS";
	int titleX = (g->x - strlen(title)) / 2;

	//draw the top border around the title
	mvhwall(0, 0 , 0x250C, 0x2500, 0x2500, titleX - 1);
	mvhwall(0, titleX + strlen(title) + 1 , 0x2500, 0x2500, 0x2510, g->x - (titleX + strlen(title) + 1));

	//draw the title
	attron(A_BOLD);
	mvprintw(0, titleX, title);
	attroff(A_BOLD);

	//draw the side vertical borders
	mvvwall(1, 0, 0x2502, g->y - 2);
	mvvwall(1, g->x - 1, 0x2502, g->y - 2);

	//draw the bottom border
	mvhwall(g->y - 1, 0 , 0x2514, 0x2500, 0x2518, g->x);

	refresh();
}

//moves the cursor and draws a horizontal wall with the specified characters
void mvhwall(int y, int x, wchar_t start, wchar_t mid, wchar_t end, int n) {
	if (n >= 2) {
		wchar_t *c = malloc(sizeof(wchar_t) * (n + 1));

		c[0] = start;
		c[n - 1] = end;
		for (int i = 1; i < n - 1; ++i) {
			c[i] = mid;
		}
		c[n] = L'\0';	

		mvaddwstr(y, x, c);
	}
}

//moves the cursor and draws a vertical wall with the specified character
void mvvwall(int y, int x, wchar_t w, int n) {
	cchar_t *c = malloc(sizeof(cchar_t));
	c->chars[0] = w;
	c->chars[1] = L'\0';
	
	for (int i = 0; i < n; ++i) mvadd_wch(y + i, x, c);
}
		
