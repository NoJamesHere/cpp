#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <list>
#include <ncurses.h>
#include <nlohmann/json.hpp>
#include <random>
#include <string>
#include <unistd.h>
using json = nlohmann::json;

namespace main_program {
// --- Structs ---

struct listing {
  std::string name;
  int amount;
  bool craft;
  static std::vector<listing> all_parts;
};

struct quest {
  std::string title;
  std::string description;
  int requiredPartIndex;
  int requiredAmount;
  bool completed;

  static std::vector<quest> all_quests;
};

struct crafting {
  int indexOfCraftedPart;
  int indexOfPart1;
  int indexOfPart2;
  int amount1;
  int amount2;

  static std::vector<crafting> recipes;
};

// --- Lists & Vectors ---

std::vector<quest> quest::all_quests = {
    {"First steps", "Circuit Boards are fundamental. Craft 2 of them.", 0, 2,
     false},
    {"Power", "Obtain 2 Power Cores.", 1, 2, false},
    {"Fusion what?", "Obtain 2 Fusion Cores.", 5, 2, false},
};

std::vector<crafting> crafting::recipes = {
    {5, 0, 1, 2, 4},
};

std::vector<listing> listing::all_parts = {
    {"Circuit Board", 0, false}, {"Power Core", 0, false},
    {"Nano Alloy", 0, false},    {"Cooling Module", 0, false},
    {"Quantum Drive", 0, false}, {"Fusion Core", 0, true},
};

std::list<std::string> words{
    "somebody", "have",  "time",  "person", "year", "way",   "day",
    "man",      "thing", "world", "life",   "name", "water", "father",
    "house",    "story", "book",  "home",   "so",   "very",  "and",
    "good",     "new",   "first", "last",   "and",  "when",  "friend",
    "power",    "city",  "a",     "an",     "the",  "their", "want",
    "look",     "give",  "find",  "work",   "ask",  "seem",  "feel",

};

const int length_words_list = words.size();

// --- Save & Load ---

void save_game() {
  json data;

  for (const auto &part : listing::all_parts) {
    data["parts"].push_back(
        {{"name", part.name}, {"amount", part.amount}, {"craft", part.craft}});
  }

  for (const auto &q : quest::all_quests) {
    data["quests"].push_back({{"title", q.title},
                              {"description", q.description},
                              {"requiredPartIndex", q.requiredPartIndex},
                              {"requiredAmount", q.requiredAmount},
                              {"completed", q.completed}});
  }

  std::ofstream file("save.json");
  file << data.dump(4);
  file.close();
}

void load_game() {
  std::ifstream file("save.json");
  if (!file.is_open())
    return;

  json data;
  file >> data;
  file.close();

  if (data.contains("parts")) {
    for (size_t i = 0; i < listing::all_parts.size(); i++) {
      listing::all_parts[i].amount = data["parts"][i]["amount"];
    }
  }

  if (data.contains("quests")) {
    for (size_t i = 0; i < quest::all_quests.size(); i++) {
      quest::all_quests[i].completed = data["quests"][i]["completed"];
    }
  }
}

// --- Typing Game ---

// Calculating Accuracy
int wtfs_leventshtein(std::string &generated, std::string &user_input) {
  int n = generated.size();
  int m = user_input.size();
  std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1));

  for (int i = 0; i <= n; i++)
    dp[i][0] = i;
  for (int j = 0; j <= m; j++)
    dp[0][j] = j;

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      if (generated[i - 1] == user_input[j - 1]) { // wtf is going on here
        dp[i][j] = dp[i - 1][j - 1];
      } else {
        dp[i][j] = 1 + std::min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
      }
    }
  }
  return dp[n][m];
}

double accuracy_calc(std::string &a, std::string &b) {
  int dist = wtfs_leventshtein(a, b);
  int maxLen = std::max(a.size(), b.size());
  if (maxLen == 0)
    return 100.0;
  return 100.0 * (1.0 - (double)dist / maxLen);
}

// Sentence Generator
int randoms(int lo, int hi) {
  static std::random_device rd;
  static std::mt19937 rng(rd());
  std::uniform_int_distribution<int> dist(lo, hi);
  return dist(rng);
}

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
}

// Typing Game Logic
int typing() {
  clear();
  refresh();

  const int max_x = getmaxx(stdscr);
  const int max_y = getmaxy(stdscr);
  std::string sentence = sentence_gen();
  std::string user_input;
  int ch;
  int score;

  mvprintw((max_y / 2), (max_x / 2 - sentence.size() / 2), "%s",
           sentence.c_str());

  move(max_y / 2 + 1, max_x / 2 - sentence.size() / 2);

  while ((ch = getch()) != '\n') {
    if (ch == KEY_BACKSPACE || ch == 127) { // my eyes hurt..
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

  double acc = accuracy_calc(user_input, sentence);

  if (acc == 100.0)
    score = 2;
  else if (acc >= 80.0 && acc < 100.0)
    score = 1;
  else
    score = 0;

  if (score == 2) {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "PERFECT!! (+2)");
  } else if (score == 1) {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "Typed: %s", user_input.c_str());
    mvprintw(max_y / 2 - 5, max_x / 2 - 5,
             "Manufactured product is corrupt (+1).");
  } else {
    mvprintw(max_y / 2 + 3, max_x / 2 - 5, "Typed: %s", user_input.c_str());
    mvprintw(max_y / 2 - 5, max_x / 2 - 5, "Failed to manufacture.");
  }

  refresh();
  getch();
  return score;
}

// reset lines
void resetsomething(int my) { mvprintw(my / 3 - 1, 10, "             "); }

// Add manufactured amount
void startTyper(int list_some) {
  int accurate_int = typing();
  if (accurate_int == 2) {
    listing::all_parts[list_some].amount += 2;
  } else if (accurate_int == 1) {
    listing::all_parts[list_some].amount += 1;
  }
}

// --- Crafting Logic ---

bool checkItemParts(int recipeIndex) {
  auto &recipe = crafting::recipes[recipeIndex];
  auto &part1 = listing::all_parts[recipe.indexOfPart1];
  auto &part2 = listing::all_parts[recipe.indexOfPart2];

  if (part1.amount >= recipe.amount1 && part2.amount >= recipe.amount2) {
    part1.amount -= recipe.amount1;
    part2.amount -= recipe.amount2;
    return true;
  }
  return false;
}

// --- Quest Logic ---

// "What's the next uncompleted quest?"
int next_quest() {
  for (int i = 0; i < quest::all_quests.size(); i++) {
    if (quest::all_quests[i].completed) {
      continue;
    } else {
      return i;
    }
  }
  return 0;
}

void check_current_quest_completion(int QuestIndex) {
  int requiredAmount = quest::all_quests[QuestIndex].requiredAmount;
  int requiredPartIndex = quest::all_quests[QuestIndex].requiredPartIndex;
  int currentAmount = listing::all_parts[requiredPartIndex].amount;

  if (currentAmount >= requiredAmount) {
    quest::all_quests[QuestIndex].completed = true;
  }
}

// --- Main Screen ---

void main_game() {
  const int max_x = getmaxx(stdscr);
  const int max_y = getmaxy(stdscr);
  int list_some = 0;
  std::string name = "";
  int currentQuestIndex;
  while (true) {
    currentQuestIndex = next_quest();
    std::string currentQuestTitle = quest::all_quests[currentQuestIndex].title;
    std::string currentQuestDescription =
        quest::all_quests[currentQuestIndex].description;
    int currentQuestRequiredPart =
        quest::all_quests[currentQuestIndex].requiredPartIndex;
    int currentQuestRequiredAmount =
        quest::all_quests[currentQuestIndex].requiredAmount;
    int currentQuestCurrentAmount =
        listing::all_parts[currentQuestRequiredPart].amount;
    check_current_quest_completion(currentQuestIndex);
    refresh();
    clear();
    int row = max_y / 2;
    for (int i = 0; i < listing::all_parts.size(); i++) {
      if (i == list_some)
        attron(A_REVERSE);
      mvprintw(row + i, max_x / 2, "%s", listing::all_parts[i].name.c_str());
      mvprintw(row + i, max_x / 2 + listing::all_parts[i].name.size() + 2, "%d",
               listing::all_parts[i].amount);
      attroff(A_REVERSE);
    }

    mvprintw(max_y / 2 - 7, 10,
             "Press Up/Down and hit Enter to manufacture those.. ( (q)uit");
    mvprintw(max_y / 2 - 4, 10, "Complete quest: \"%s\"",
             currentQuestTitle.c_str());
    mvprintw(max_y / 2 - 2, 10, "\"%s\"", currentQuestDescription.c_str());
    mvprintw(max_y / 2 - 1, 10, "%d / %d", currentQuestCurrentAmount,
             currentQuestRequiredAmount);

    refresh();
    int ch = getch();
    switch (ch) {
    case KEY_UP:
      list_some--;
      break;
    case KEY_DOWN:
      list_some++;
      break;
    case 'q':
      save_game();
      endwin();
      return;
    case '\n':
    case KEY_ENTER:
      auto &item = listing::all_parts[list_some];
      if (item.craft) {
        auto it = std::find_if(
            crafting::recipes.begin(), crafting::recipes.end(),
            [&](auto &r) { return r.indexOfCraftedPart == list_some; });
        if (it != crafting::recipes.end() &&
            checkItemParts(it - crafting::recipes.begin())) {
          startTyper(list_some);
        } else {
          auto &ingredient1 = listing::all_parts[it->indexOfPart1];
          auto &ingredient2 = listing::all_parts[it->indexOfPart2];
          int amount1 = it->amount1;
          auto &amount2 = it->amount2;
          mvprintw(max_y - 5, 2, "Not enough parts!!");
          mvprintw(max_y - 4, 2, "You need:");
          mvprintw(max_y - 3, 2, "%s: %d", ingredient1.name.c_str(), amount1);
          mvprintw(max_y - 2, 2, "%s: %d", ingredient2.name.c_str(), amount2);
          getch();
        }
      } else
        startTyper(list_some);
      break;
      /*case ERR:
        break;*/
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
  nodelay(stdscr, FALSE);
  keypad(stdscr, TRUE); // enable function keys and arrow keys
  load_game();
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
