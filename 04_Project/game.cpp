// important !! this scripts a bit broken and I am way too tired, good luck future me

#include <iterator>
#include <list>
#include <ncurses.h>
#include <random>
#include <string>
#include <unistd.h>
#include <algorithm>
namespace main_program {
int chips = 0;
int storage = 0;

int wtfs_leventshtein(std::string& generated, std::string& user_input){
  int n = generated.size();
  int m = user_input.size();
  std::vector<std::vector<int>> dp(n+1, std::vector<int>(m+1));

  for(int i=0; i<=n; i++) dp[i][0] = i;
  for(int j=0; j<=m; j++) dp[0][j] = j;

  for (int i = 0; i <= n; i++){
    for (int j = 0; j <= m; j++){
      if (generated[i-1] == user_input[j-1]){ // wtf is going on here
        dp[i][j]= dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + std::min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
      }
    }
  }
  return dp[n][m];
}

double accuracy_calc(const std::string& a, const std::string& b){
  int dist = wtfs_leventshtein(a,b);
  int maxLen = std::max(a.size(), b.size());
  return 100.0 * (1.0 - (double)dist / maxLen);
}
struct listing{
  std::string name;
  int amount;

  static std::vector<listing> all_parts;
};

std::vector<listing> listing::all_parts = {
  {"Chips", 0},
  {"storage", 0}
};


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
  for (int i = 0; i < 10; i++) { // 10 Words (or 11? idk)
    int number = randoms(0, length_words_list - 1);
    auto it = words.begin(); // iterator
    std::advance(it, number);
    sentence += *it + " ";
  }
  int number = randoms(0, length_words_list - 1);
  auto it = words.begin();
  std::advance(it, number);
  sentence += *it;
  return sentence;
} // Sentence generator

int typing() {
  
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
    if (ch == KEY_BACKSPACE || ch == 127) {  // my eyes hurt..
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
  int score;
  double acc = accuracy_calc(user_input, sentence);

  if (acc == 100.0) score = 2;
  else if (acc >= 80.0 && acc < 100.0) score = 1;
  else score = 0;

  if (score == 2) {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "PERFECT!!");
  } else if (score == 1) {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "Typed: %s", user_input.c_str());
    mvprintw(max_y / 2 - 5, max_x / 2 - 5, "Failed to manufacture.");
  } else {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "Typed: %s", user_input.c_str());
    mvprintw(max_y / 2 - 5, max_x / 2 - 5, "Failed to manufacture.");

  }
  refresh();
  getch();
  return score;
} // Typing game functionality


// reset lines
void resetsomething(int my) { mvprintw(my / 3 - 1, 10, "             "); }

void main_game() {
  nodelay(stdscr, TRUE);
  const int max_x = getmaxx(stdscr);
  const int max_y = getmaxy(stdscr);
  int list_some = 0;
  std::string name = "";
  while (true) {
    clear();
    int row = max_y / 2;
    for (int i = 0; i < listing::all_parts.size(); i++) {
      if (i == list_some)
        attron(A_REVERSE);
      mvprintw(row + i, max_x / 2, "%s", listing::all_parts[i].name.c_str());
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
      endwin();
      return;
    case 10:
    case KEY_ENTER:
      int accurate_int = typing();
      if(accurate_int == 2){
        listing::all_parts[list_some].amount += 2;
        }
      else if (accurate_int == 1){
          listing::all_parts[list_some].amount += 1;
        }
      break;

    case ERR:
      break;
    }
    if (list_some < 0)
      list_some = 0;
    if (list_some >= listing::all_parts.size())
      list_some = listing::all_parts.size() - 1;
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
