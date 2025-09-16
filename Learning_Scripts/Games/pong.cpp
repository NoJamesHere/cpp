#include <cmath>
#include <ncurses.h>
#include <unistd.h>

void game() {
  start_color();
  init_pair(1, COLOR_BLACK, COLOR_GREEN); // ID 1 = green background
  init_pair(2, COLOR_BLACK, COLOR_RED);   // ID 2 = red background
  int score_flash_timer = 0;
  int score_flash = 0;
  int y = 10, x = 20;
  int dx = 1, dy = 1;
  int px = 5, py = 10;
  int max_y, max_x;
  bool movingUp = false;
  bool movingDown = false;
  int score = 0;
  int previous_score = 0;
  int old_y = y, old_x = x, old_py = py, old_px = px;
  getmaxyx(stdscr, max_y, max_x); // stdscr = default window
  while (true) {

    old_y = y;
    old_x = x;
    old_py = py;
    old_px = px;

    x += dx;
    y += dy;

    int ch = getch();
    switch (ch) {
    case 'w':
      movingUp = true;
      movingDown = false;
      break;
    case 's':
      movingDown = true;
      movingUp = false;
      break;
    case 'q':
      return;
    case ERR:
      break;
    }

    if (movingUp)
      py -= 2;
    if (movingDown)
      py += 2;

    usleep(40000);

    if (py < 2)
      py = 2;
    if (py >= max_y - 3)
      py = max_y - 3;
    if (x >= max_x - 1 || x <= 0) {
      dx = -dx;
    } else if (x <= px + 2 && x <= px - 2) {
      if (y <= py + 4 && y >= py - 4) {
        dx = abs(dx);
        score++;
        score_flash = 1; // green
        score_flash_timer = 50;
      } else if (x <= px) {
        score--;
        x = max_x / 2;
        y = max_y / 2;
        dx = abs(dx);
        score_flash = 2;        // red
        score_flash_timer = 50; // 50 = 50 frames
      }
    }
    if (y >= max_y - 1 || y <= 0) {
      dy = -dy;
    }
    mvprintw(old_y, old_x, " ");
    if (old_py != py) {
      for (int i = -2; i <= 2; i++) {
        mvprintw(old_py + i, px, "   ");
      }
    }
    mvprintw(y, x, "O");
    for (int i = -2; i <= 2; i++) {
      mvprintw(py + i, px, "I I");
    }

    if (score_flash_timer > 0) {
      attron(COLOR_PAIR(score_flash)); // display color
      mvprintw(max_y - 1, 45, "   ");
      attroff(COLOR_PAIR(score_flash));
      score_flash_timer--;
    } else {
      mvprintw(max_y - 1, 45, "   ");
      attroff(COLOR_PAIR(score_flash));
    }
    previous_score = score;

    mvprintw(max_y - 1, 50, "Score: %d", score);

    refresh();
  }
}

int main() {
  initscr();
  noecho(); // |  Setting things up here
  curs_set(FALSE);
  nodelay(stdscr, TRUE);

  game();
  endwin();
  return 0;
}
