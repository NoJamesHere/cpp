#include <iostream>
#include <ncurses.h>
int main() {
  initscr();             // |
  noecho();              // |  Setting things
  curs_set(FALSE);       // |     up here
  nodelay(stdscr, TRUE); // |
  start_color();
  init_pair(1, COLOR_GREEN, COLOR_BLACK);

  if (!has_colors()) {
    endwin();
    std::cout << "Your console does not support colors.." << std::endl;
    return 1;
  }
  while (true) {
    attron(COLOR_PAIR(1)); // red
    mvprintw(50 - 1, 48, " ");
    refresh();
    napms(50);
  }
  return 0;
}
