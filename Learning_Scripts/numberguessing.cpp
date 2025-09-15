#include <algorithm>
#include <cstdlib>
#include <list>
#include <random>
#include <stdio.h>
#include <string>

namespace number {
void guessing() {
  bool running = true;
  std::list<char> difficulty_list = {'e', 'm', 'h'};
  int end{};
  int count{};
  while (running) {
    char input;
    printf("\n\033[1;37m=====================\n"
           "• \033[32m(e)asy\033[37m:   max 10\n"
           "• \033[33m(m)edium\033[37m: max 50\n"
           "• \033[31m(h)ard\033[37m:   max 150\n"
           "=====================\033[0m\n\n");
    printf("\033[1;3;34mDifficulty?: \033[0m");
    scanf(" %c", &input);
    // randomizing
    std::random_device rd;

    if (std::find(difficulty_list.begin(), difficulty_list.end(), input) !=
        difficulty_list.end()) {
      bool found = false;
      if (input == 'e') {
        end = 10;
      } else if (input == 'm') {
        end = 50;
      } else {
        end = 150;
      }
      std::mt19937 gen(rd());
      std::uniform_int_distribution<> dist(1, end);
      int random_number = dist(gen);
      count = 0;
      while (!found) {
        count++;
        int choice{}; // possible bug: if user enters a string or similar,
                      // yeah..
        printf("\n\nWhat \033[1;33mnumber\033[0m are you thinking?: ");
        scanf(" %d", &choice);
        if (choice == random_number) {
          printf("\n\n\033[1;36mYou found it!! The number \033[33m%d\033[36m "
                 "was correct!!\n\033[47;30m(Tries: %d)\033[0m",
                 random_number, count);
          found = true;
          printf("\nDo you want to play again? (y/n): ");
          scanf(" %c", &input);
          if (input == 'y') {
            continue;
          } else
            running = false;
        } else {
          std::string lower_higher = "";
          if (choice > random_number) {
            lower_higher = "lower";
          } else {
            lower_higher = "higher";
          }
          printf("Hmmm %d was not the right answer.. Try "
                 "again! (\033[1;33m%s\033[0m)\n\n",
                 choice, lower_higher.c_str());
        }
      }
    } else if (input == 'q') {
      running = false;
    } else
      printf("Your choice %c was not a valid option", input);
  }
}
} // namespace number

int main() {
  number::guessing();
  return 0;
}
