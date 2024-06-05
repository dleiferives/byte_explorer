#include "tui.h"
void Terminal_t_create(Terminal_t *t) {
  // sets up the terminal
  if (setupterm(0, 1, 0)) {
    fprintf(stderr, "setupterm failed");
    exit(1);
  }
  // sets the cursor up
  if (!(t->cu = tigetstr("cup"))) {
    fprintf(stderr, "no cursor addressing in terminal");
    exit(1);
  }
  // sets the screen cursor up
  tputs(tigetstr("smcup"), 1, putchar);
  // fills in the width and height
  t->width = tigetnum((char *)"cols");
  t->height = tigetnum((char *)"lines");

  // if there is no good data from one or both. just dont do anything
  if ((t->width < 1) || (t->height < 1)) {
    fprintf(stderr, "could not read the size of terminal");
    exit(1);
  }
}

void Terminal_t_destroy() {
  tputs(tigetstr("rmcup"), 1, putchar);
  tputs(tiparm(tigetstr("cnorm")), 1, putchar);
}

void Terminal_t_cursor_invis(void) {
  tputs(tiparm(tigetstr("civis")), 1, putchar);
}

void Terminal_t_move_cursor(Terminal_t *t, unsigned short x, unsigned y) {
  tputs(tiparm(t->cu, y, x), 1, putchar);
}

void Terminal_t_repeat_char(Terminal_t *t, char c, int n) {
  tputs(tiparm(tigetstr("rep"), c, n), 1, putchar);
}

void Terminal_t_delete_lines(Terminal_t *t, int n) {
  tputs(tiparm(tigetstr("dl"), n), 1, putchar);
}

void Terminal_t_clear_to_screen_end(Terminal_t *t) {
  tputs(tiparm(tigetstr("ed")), 1, putchar);
}

void Terminal_t_clear_to_l_end(Terminal_t *t) {
  tputs(tiparm(tigetstr("el")), 1, putchar);
}

Terminal_t Terminal_t_init(void) {
  Terminal_t result;
  result.width = 0;
  result.height = 0;
  result.buffer = NULL;
  result.rep_buffer = NULL;
  result.cu = NULL;
  return result;
}

