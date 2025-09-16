#include <ncurses.h>
#include <unistd.h>

namespace animation_one {

void reset() {
  for (int i = 0; i < 4; i++) {
    mvprintw(10 + i, 10 + i, "      ");
    mvprintw(30 - i, 30 - i, "      ");
    refresh();
    usleep(50000);
  }
  mvprintw(5, 5, "                    ");
  return;
}

void anima() {
  bool running = true;
  while (running) {
  restart_animation:;
    mvprintw(5, 5, "Looks cool..");
    for (int i = 0; i < 4; i++) {
      mvprintw(10 + i, 10 + i, "******");
      mvprintw(30 - i, 30 - i, "******");
      int input = getch();
      switch (input) {
      case 'q':
        running = false;
        reset();
        return;
      case 'r':
        reset();
        goto restart_animation;
      }
      usleep(500000);
      refresh();
    }
  }
}
} // namespace animation_one

// why the fuck does it look like that :sob:
namespace animation_two {

void reset() {
  for (int i = 0; i < 20; i++) {
    for (int j = 0; j < 10; j++) {
      mvprintw(25 + j, 25 + i, "       ");
    }
  }
  mvprintw(5, 5, "           ");
  refresh();
  return;
}

void anima() {
  bool running = true;
  while (running) {
  restart_animation:;
    mvprintw(5, 5, "S q a r e");

    for (int i = 0; i < 20; i++) {
      for (int j = 0; j < 10; j++) {
        mvprintw(25 + j, 25 + i, "#");
        int input = getch();
        switch (input) {
        case 'q':
          reset();
          running = false;
          return;
        case 'r': // resetting animation here:
          reset();
          goto restart_animation;
        }
        usleep(50000);
        refresh();
      }
      refresh();
    }
  }
}
} // namespace animation_two

namespace animation_three {
void reset(int mx, int my, int lines) {
  for (int i = 0; i < lines; i++) {
    mvprintw((my / 2) + i, (mx / 2) + i, " ");
    usleep(5000);
    refresh();
  }
  mvprintw(5, mx / 2, "                     ");
  refresh();
}

void anima() {

  bool running = true;
  int max_x, max_y;
  getmaxyx(stdscr, max_y, max_x);
  int lines = 20;
  while (running) {
  restart_animation:;
    mvprintw(5, max_x / 2, "I don't know");
    for (int i = 0; i < lines; i++) {
      int input = getch();
      switch (input) {
      case 'q':
        reset(max_x, max_y, lines);
        running = false;
        return;
      case 'r':
        reset(max_x, max_y, lines);
        goto restart_animation;
      }
      mvprintw((max_y / 2) + i, (max_x / 2) + i, "^");
      usleep(50000);
      refresh();
    }
  }
}
} // namespace animation_three

int main() {
  initscr();
  noecho();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  animation_one::anima();
  animation_two::anima();
  animation_three::anima();
  endwin();
  return 0;
}
