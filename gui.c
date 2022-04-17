#include "gui.h"

const int MIN_X = 0, MIN_Y = 0;



//start ncurses mode, returns false if window size is smaller than chess board
bool InitGUI(GUI *g) {
	g->state = MENU; 

	initscr();
	curs_set(0);
	noecho();
	cbreak();

	//weird stuff to make mouse work
	keypad(stdscr, true);
	printf("\033[?1002h\n"); //xterm report mouse button events (NO MOVEMENT EVENTS)

	//set up mouse event
	mousemask(BUTTON1_PRESSED, NULL);

	getmaxyx(stdscr, g->y, g->x);
	wattrset(stdscr, A_NORMAL);

	//setup menu and options
	g->menu = malloc(sizeof(Menu));
	g->menu->size = 2;
	g->menu->settings = calloc(2, sizeof(MenuSetting *));

	//GAMEMODE OPTIONS
	g->menu->settings[0] = malloc(sizeof(MenuSetting));
	g->menu->gamemode = g->menu->settings[0];
	g->menu->settings[0]->text = "GAMEMODE:";
	g->menu->settings[0]->size = 2;
	g->menu->settings[0]->selected = -1;
	//	allocate space
	g->menu->settings[0]->options = calloc(2, sizeof(MenuOption *));
	g->menu->settings[0]->options[0] = malloc(sizeof(MenuOption));
	g->menu->settings[0]->options[1] = malloc(sizeof(MenuOption));
	//	option0, tutorial
	g->menu->settings[0]->options[0]->text = "TUTORIAL";
       	g->menu->settings[0]->options[0]->value = 0;
	//	option1, player vs ai
	g->menu->settings[0]->options[1]->text = "PLAYER VS AI";
       	g->menu->settings[0]->options[1]->value = 1;
	SetBox(g->menu->settings[0], g->y, g->x, 4); 	


	//DIFFICULTY OPTIONS
	g->menu->settings[1] = malloc(sizeof(MenuSetting));
	g->menu->difficulty = g->menu->settings[1];
	g->menu->settings[1]->text = "DIFFICULTY:";
	g->menu->settings[1]->size = 3;
	g->menu->settings[1]->selected = -1;
	//	allocate space
	g->menu->settings[1]->options = calloc(3, sizeof(MenuOption *));
	g->menu->settings[1]->options[0] = malloc(sizeof(MenuOption));
	g->menu->settings[1]->options[1] = malloc(sizeof(MenuOption));
	g->menu->settings[1]->options[2] = malloc(sizeof(MenuOption));
	//	option0, tutorial
	g->menu->settings[1]->options[0]->text = "BEGINNER";
       	g->menu->settings[1]->options[0]->value = 0;
	//	option1, player vs ai
	g->menu->settings[1]->options[1]->text = "INTERMEDIATE";
       	g->menu->settings[1]->options[1]->value = 1;
	//	option2
	g->menu->settings[1]->options[2]->text = "EXPERT";
       	g->menu->settings[1]->options[2]->value = 2;
	SetBox(g->menu->settings[1], g->y, g->x, 6); 	
	
	//START BUTTON
	g->menu->start.x0 = (g->x - 10)/2;
	g->menu->start.x1 = g->menu->start.x0 + 9;
	g->menu->start.y1 = g->menu->start.y0 = g->y - 5;	

	//EXIT BUTTON
	g->menu->exit.x0 = (g->x - 4)/2;
	g->menu->exit.x1 = g->menu->exit.x0 + 3;
	g->menu->exit.y1 = g->menu->exit.y0 = g->y - 3;	
	
	if (g->y < MIN_Y || g->x < MIN_X) return false;
	else return true;
}



//frees GUI structs and deconstructs ncurses
void Cleanup(GUI *g) {
	echo();
	nocbreak();
	endwin();
	printf("\033[?1002l\n"); //disable mouse reporting
	//ughhhhhh pointers	
	
	//free menu and children
	for (int i = 0; i < g->menu->size; ++i) {
		MenuSetting *curSet = g->menu->settings[i];
		for (int j = 0; j < curSet->size; ++j) {
			free(curSet->options[j]);
		}
		free(curSet->options);
		free(curSet);	
	}
	free(g->menu->settings);
	free(g->menu);

	//free and unset gui pointer
	free(g);
	g = NULL;

	system("clear");
	//raise(SIGINT);
}
	


//to be called in main game loop, handles the entire GUI operation
void DoGUI(GUI *g) {
	//handle mouse input	
	MEVENT e;
	int ch = wgetch(stdscr);

	if (ch == KEY_MOUSE) {
		if (getmouse(&e) == OK) {
			if (e.bstate & (BUTTON1_PRESSED)) { 
				HandleMouse(g, e);
			}
		}
	}

	flushinp();

	//handle gui drawing
	switch (g->state) {
		case MENU:
			DrawMenu(g);
		break;
		case GAME:
			DrawGame(g);
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

	//iterate over every setting, print the label	
	for (int s = 0; s < g->menu->size; ++s) {
		mvprintw(g->menu->settings[s]->labelY, g->menu->settings[s]->labelX, g->menu->settings[s]->text);
		//iterater over every option of the setting, printing each
		for (int o = 0; o < g->menu->settings[s]->size; ++o) {
			if (g->menu->settings[s]->selected == o) attron(A_BOLD);
			mvprintw(g->menu->settings[s]->options[o]->bound.y0, g->menu->settings[s]->options[o]->bound.x0, g->menu->settings[s]->options[o]->text);
			attroff(A_BOLD);
		}
	}
		
	//print the start button
	//mvprintw(g->menu->start.y0, g->menu->start.x0, "START GAME");
	
	//print the quit button
	mvprintw(g->menu->exit.y0, g->menu->exit.x0, "QUIT");

	refresh();
}



void DrawGame(GUI *g) {
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
	
	//setup chess board window
	//35w 17h
	int bh = 17, bw = 35;
	g->game->bWin = newwin(bh, bw, (g->y - bh)/2, (g->x - bw)/2);
	box(g->game->bWin, 0, 0);

	wrefresh(g->game->bWin);
	refresh();
}



void HandleMouse(GUI *g, MEVENT e) {
	switch(g->state) {
		case MENU:
			//iterate over every setting, print the label	
			for (int s = 0; s < g->menu->size; ++s) {
				mvprintw(g->menu->settings[s]->labelY, g->menu->settings[s]->labelX, g->menu->settings[s]->text);
				//iterater over every option of the setting, printing each
				for (int o = 0; o < g->menu->settings[s]->size; ++o) {
					if (IsInBox(e.y, e.x, g->menu->settings[s]->options[o]->bound))
						g->menu->settings[s]->selected = o;	
				}
			}

			//if (IsInBox(e.y, e.x, g->menu->start)) g->state = GAME;
			if (IsInBox(e.y, e.x, g->menu->exit)) g->state = EXITING;
		break;
	}
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
		free(c);
	}
}



//moves the cursor and draws a vertical wall with the specified character
void mvvwall(int y, int x, wchar_t w, int n) {
	cchar_t *c = malloc(sizeof(cchar_t));
	c->chars[0] = w;
	c->chars[1] = L'\0';
	
	for (int i = 0; i < n; ++i) mvadd_wch(y + i, x, c);
	free(c);
}
		


bool IsInBox(int y, int x, Box b) {
	return y >= b.y0 && y <= b.y1 && x >= b.x0 && x <= b.x1;
}



void SetBox(MenuSetting *s, int height, int width, int y) {
	s->labelX = width - strlen(s->text);

	//calculate left margin for centering, 4 char spacing
	for (int i = 0; i < s->size; ++i) {
		s->labelX -= 4 + strlen(s->options[i]->text);
	}

	s->labelX = s->labelX / 2;
	s->labelY = y;

	s->options[0]->bound.x0 = s->labelX + strlen(s->text) + 4;
	s->options[0]->bound.y0 = y;
	s->options[0]->bound.x1 = s->options[0]->bound.x0 + strlen(s->options[0]->text) - 1;
	s->options[0]->bound.y1 = y;
	for (int i = 1; i < s->size; ++i) {
		s->options[i]->bound.x0 = s->options[i-1]->bound.x0 + strlen(s->options[i-1]->text) + 4;
		s->options[i]->bound.y0 = y;
		s->options[i]->bound.x1 = s->options[i]->bound.x0 + strlen(s->options[i]->text) - 1;
		s->options[i]->bound.y1 = y;
	}
}