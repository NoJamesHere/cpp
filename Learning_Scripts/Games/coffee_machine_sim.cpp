#include <algorithm>
#include <chrono>
#include <iostream>
#include <list>
#include <stdio.h>
#include <string>
#include <thread>

#ifdef _WIN32
#include <windows.h>
void enable_virtual_terminal() {
  HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
  DWORD dwMode = 0;
  GetConsoleMode(hOut, &dwMode);
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  SetConsoleMode(hOut, dwMode);
}
#endif

// lets just see how we can optimize this code
bool check(int water_needed, int current_water, int current_beans,
           int cost_beans) {
  if ((current_water >= water_needed) && (current_beans >= cost_beans)) {

    return true;
  } else
    return false;
}

void refined_coffee_machine() {
  std::list<char> coffee_types{'a', 'e', 'd'};
  bool running(true);
  int current_water = 500;
  int current_coffee_beans = 10;
  // we will use this for the options (if input == "a" etc)
  int water_needed = 0;
  const char *frames[] = {
      "[=           ]", "[==          ]", "[===         ]", "[====        ]",
      "[=====       ]", "[======      ]", "[=======     ]", "[========    ]",
      "[=========   ]", "[==========  ]", "[==========  ]", "[=========== ]",
      "[============]",
  };

  int num_of_frames_bar = sizeof(frames) / sizeof(frames[0]);

  const int cost_beans = 2;
  const int water_cost_espresso = 30;
  const int water_cost_americano = 180;
  const int water_cost_espresso_doppio = 50;
  std::string not_enough = "water";
  std::string current_type = "none";
  char input;
  printf("\033[3;37mPress 'Q' to quit\033[0m\n");
  printf("\033[1;37m==============================\n"
         "  COFFEE MACHINE SIMULATOR  \n"
         "       By NoJamesHere       \n"
         "==============================\033[0m\n\n");
  // -- Main part of the program --
  while (running) {
    printf("\n\033[1;33mLEFT: %d ml water, %d beans\n\n\033[0m", current_water,
           current_coffee_beans);
    printf("\033[1;37mMENU:\n"
           "================\n"
           "• (a): Americano\n"
           "• (e): Espresso\n"
           "• (d): Espresso Doppio\n"
           "================\n\033[0m");
    printf("\033[3;33mChoice?: \033[0m");
    scanf(" %c", &input); // note to self: do not forget this whitespace.
    printf("\n");
    if (std::find(coffee_types.begin(), coffee_types.end(), input) !=
        coffee_types.end()) {
      if (input == 'a') { // americano
        water_needed = water_cost_americano;
        current_type = "americano";
      } else if (input == 'e') { // espresso
        water_needed = water_cost_espresso;
        current_type = "espresso";
      } else { // doppio
        water_needed = water_cost_espresso_doppio;
        current_type = "espresso doppio";
      }
      bool able_to =
          check(water_needed, current_water, current_coffee_beans, cost_beans);
      if (able_to) {
        current_water -= water_needed;
        current_coffee_beans -= cost_beans;
        // i want a loading screen.

        int i = 0;
        while (i < num_of_frames_bar) {
          std::cout << "\r" << "\033[1;37;44m" << frames[i % num_of_frames_bar]
                    << "\033[0m" << std::flush;
          std::this_thread::sleep_for(std::chrono::milliseconds(200));
          i++;
        }
        printf("\n\033[3;1;32mDing!\033[0m\n");

        std::this_thread::sleep_for(std::chrono::milliseconds(500));

        printf("\nEnjoy your \033[1;33m %s\033[0m!!\n\n", current_type.c_str());
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
      } else {
        if (current_water < water_needed) {
          if (current_coffee_beans < cost_beans) {
            not_enough = "water and beans";
          } else {
            not_enough = "water";
          }
        } else {
          not_enough = "beans";
        }
        printf(
            "\033[3;35mNot enough %s.. Please refill.. \033[1;33m(r)\033[0m\n",
            not_enough.c_str()); // could put this into a function or somehow
                                 // reusable code
      }
    } else if (input == 'r') {
      int i = 0;
      // two bars, one for water, one for the beans
      while (i < num_of_frames_bar) {
        std::cout << "\r" << "\033[1;37;44m" << frames[i % num_of_frames_bar]
                  << "\033[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        i++;
      }
      printf("\n\033[1;33m(1/2)\033[0m Done\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      i = 0;
      while (i < num_of_frames_bar) {
        std::cout << "\r" << "\033[1;48;2;0;0;0m\033[38;2;255;255;255m"
                  << frames[i % num_of_frames_bar] << "\033[0m" << std::flush;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        i++;
      }
      printf("\n\033[1;33m(2/2)\033[0m Done\n");
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
      i = 0;
      printf("\n\n\033[1;32mRefilled!\033[0m\n");
      current_water = 500;
      current_coffee_beans = 10;
    } else if (input == 'q') {
      printf("\033[1;37mHopefully you enjoyed..\nGoodbye!\033[0m");
      running = false;
    } else {
      printf("\033[1;35mYour choice \033[1;33m'%c'\033[1;35m is not "
             "valid..\n\033[0m",
             input);
    }
  }
}

int main() {
#ifdef _WIN32
  enable_virtual_terminal();
#endif
  refined_coffee_machine();
  return 0;
}

/*
void before_refining() {
  bool running{true};
  int current_water = 500;
  int current_coffee_beans = 1;
  // needed water for types of coffee brews
  const int cost_espresso_beans = 2;
  const int water_cost_of_espresso = 30;
  const int water_cost_of_americano = 180;
  const int water_cost_of_espresso_doppio = 50;
  std::string not_enough = "water";

  char input;
  printf("\n\nEnter 'q' to quit\n\n");
  while (running) {
    printf("\nCurrently the tank has %d ml of water, \nand the machine "
           "has %d beans left.\n\n",
           current_water, current_coffee_beans);
    printf("What coffee would you like?\n(e, a, d / espresso, americano, "
           "espresso doppio): ");
    scanf(" %c", &input);
    printf("\n");
    if (input == 'e') {
      if ((current_water >= water_cost_of_espresso) &&
          (current_coffee_beans >= cost_espresso_beans)) {
        printf("Here you have your espresso. Enjoy!\n");
        current_water -= water_cost_of_espresso;
        current_coffee_beans -= cost_espresso_beans;
      } else {
        if (current_water < water_cost_of_americano) {
          if (current_coffee_beans < cost_espresso_beans) {
            not_enough = "water and beans";
          } else {
            not_enough = "water";
          }
        } else {
          not_enough = "beans";
        }
        printf("Not enough %s.. Please refill.. (r)\n",
               not_enough.c_str()); // could put this into a function or somehow
                                    // reusable code
      }
    } else if (input == 'a') {
      if ((current_water >= water_cost_of_americano) &&
          (current_coffee_beans >= cost_espresso_beans)) {
        printf("Here you have your americano. Enjoy!\n");
        current_water -= water_cost_of_americano;
        current_coffee_beans -= cost_espresso_beans;
      } else {
        if (current_water < water_cost_of_americano &&
            current_coffee_beans < cost_espresso_beans) {
          not_enough = "water and beans";
        } else if (current_water < water_cost_of_americano) {
          not_enough = "water";

        } else {
          not_enough = "beans";
        }
        printf("Not enough %s.. Please refill... (r)\n", not_enough.c_str());
      }
    } else if (input ==
               'd') { // if input in ['d', 'e', 'a']; -> if input == 'a'; etc.
      if ((current_water >= water_cost_of_espresso_doppio) &&
          (current_coffee_beans >= cost_espresso_beans)) {
        printf("Here you have your espresso doppio. Enjoy!\n");
        current_water -= water_cost_of_espresso_doppio;
        current_coffee_beans -= cost_espresso_beans;
      } else {
        if (current_water < water_cost_of_americano &&
            current_coffee_beans < cost_espresso_beans) {
          not_enough = "water and beans";
        } else if (current_water < water_cost_of_americano) {
          not_enough = "water";

        } else {
          not_enough = "beans";
        }
        printf("Not enough %s.. Please refill... (r)\n", not_enough.c_str());
      }
    } else if (input == 'r') {
      current_water = 500;
      current_coffee_beans = 10;
      printf("Refilled your water and beans! Tank's now full! (%d ml)\n(%d "
             "beans)\n\n",
             current_water, current_coffee_beans);

    } else if (input == 'q') {
      running = false;
    } else {
      printf("Your input '%c' is not a valid option.\n", input);
    }
  }
}
*/
