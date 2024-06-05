// Little library to help me make teminal based applications.
// Dylan Leifer-Ives 9-28-2023
// It uses the term.h, which uses terminfo, which uses the ncurses library
// TODO: reimplement functions using ascii escape sequences. 
// TODO: stop depending on ncurses and get the information right out of the tty/ ssh connection
// TODO: handle errors if they occur

#include <stdio.h>
#include <term.h>
#include <stdlib.h>

#ifndef dleiferives_tui
#define dleiferives_tui

// The terminal struct that is the basis of the tui library
// width is the terminal width
// height is the terminal height
// buffer and rep_buffer are not yet implemented.
// they will be switched. And used for computing minimum character change.
typedef struct{
	int width;
	int height;
	char * buffer;
	char * rep_buffer;
	char * cu;
}Terminal_t;

// Initilizes a zeroed terminal
Terminal_t Terminal_t_init(void);

// sets up a terminal
void Terminal_t_create(Terminal_t *t);

// closes the terminal, resets the cursor by force
void Terminal_t_destroy();

// makes the cursor invisible
void Terminal_t_cursor_invis(void);

// moves the cursor to some x y
void Terminal_t_move_cursor(Terminal_t *t, unsigned short x, unsigned y);

// repeats a character n times
void Terminal_t_repeat_char(Terminal_t *t, char c, int n);

// deletes n lines -- not really working right now
void Terminal_t_delete_lines(Terminal_t *t, int n);

// clears to the screens end. this means the entire screen gets cleared
void Terminal_t_clear_to_screen_end(Terminal_t *t);

// clears to the end of the line. from the cursor to the end.
void Terminal_t_clear_to_l_end(Terminal_t *t);
#endif
