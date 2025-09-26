#include <iterator>
#include <list>
#include <ncurses.h>
#include <random>
#include <string>
#include <unistd.h>
namespace main_program {
int chips = 0;
int storage = 0;

int randoms(int lo, int hi) {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::uniform_int_distribution<int> dist(lo, hi);
  return dist(rng);
}

std::list<std::string> words{
    "somebody", "have",  "time",  "person", "year", "way",   "day",
    "man",      "thing", "world", "life",   "name", "water", "father",
    "house",    "story", "book",  "home",   "so",   "very",  "and",
    "good",     "new",   "first", "last",   "and",  "when",  "friend",
    "power",    "city",  "a",     "an",     "the",  "their", "want",
    "look",     "give",  "find",  "work",   "ask",  "seem",  "feel",

};

const int length_words_list = words.size();

std::string sentence_gen() {
  std::string sentence;
  for (int i = 0; i < 10; i++) {
    int number = randoms(0, length_words_list - 1);
    auto it = words.begin();
    std::advance(it, number);
    sentence += *it + " ";
  }
  int number = randoms(0, length_words_list - 1);
  auto it = words.begin();
  std::advance(it, number);
  sentence += *it;
  return sentence;
}

void typing() {
  nodelay(stdscr, FALSE);
  const int max_x = getmaxx(stdscr);
  const int max_y = getmaxy(stdscr);
  clear();
  refresh();
  std::string sentence = sentence_gen();
  std::string user_input;
  mvprintw((max_y / 2), (max_x / 2 - sentence.size() / 2), "%s",
           sentence.c_str());
  move(max_y / 2 + 1, max_x / 2 - sentence.size() / 2);
  int ch;
  while ((ch = getch()) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) {
      if (!user_input.empty()) {
        user_input.pop_back();
        int x, y;
        getyx(stdscr, y, x);
        mvaddch(y, x - 1, ' ');
        move(y, x - 1);
      }
    } else {
      user_input += ch;
      addch(ch);
    }
    refresh();
  }
  if (user_input == sentence) {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "PERFECT!!");
  } else {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "Typed: %s", user_input.c_str());
  }
  refresh();
  getch();
}
// reset lines
void resetsomething(int my) { mvprintw(my / 3 - 1, 10, "             "); }

void main_game() {
  nodelay(stdscr, TRUE);
  const int max_x = getmaxx(stdscr);
  const int max_y = getmaxy(stdscr);
  std::vector<std::string> parts_to_manuf{"Chip", "Storage Unit"};
  std::vector<std::string> parts_codename{"chip", "stor_un"};
  int list_some = 0;
  std::string name = "";
  while (true) {
    clear();
    int row = max_y / 2;
    for (int i = 0; i < parts_to_manuf.size(); i++) {
      if (i == list_some)
        attron(A_REVERSE);
      mvprintw(row + i, max_x / 2, "%s", parts_to_manuf[i].c_str());
      attroff(A_REVERSE);
    }
    mvprintw(max_y / 2 - 5, 10,
             "Press Up/Down and hit Enter to manufacture those.. ( (q)uit");
    refresh();
    int ch = getch();
    switch (ch) {
    case KEY_UP:
      list_some++;
      break;
    case KEY_DOWN:
      list_some--;
      break;
    case 'q':
      return;
    case 10:
    case KEY_ENTER:
      typing();
      break;
    case ERR:
      break;
    }
    if (list_some < 0)
      list_some = 0;
    if (list_some >= parts_codename.size())
      list_some = parts_codename.size() - 1;
  }
}

void initializing() {
  initscr();
  noecho();
  curs_set(FALSE);
  nodelay(stdscr, TRUE);
  keypad(stdscr, TRUE); // enable function keys and arrow keys
  main_game();
} // end of init

} // namespace main_program

int main() {
  main_program::initializing();
  return 0;
}

/*
 * The idea (for now):
 * - the main idea revolves around the player working in a factory for parts
 * - to manufacture for example a chip, the player must copy some given random
 * sentences.
 * - yeah that's basically it for now that's the core idea.
 *
 * To-Do:
 * - Make list or something with different, words: DONE
 * -> also have made a sentence generaotr
 */
