#include <chrono>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string.h>
#include <string>
#include <thread>
#include <vector>

using namespace std;

void function1() {
  int a, b, c{};
  string hi = "";
  std::cout << "Please enter three values: ";
  std::cin >> a >> b >> c;
  std::getline(std::cin, hi);
  for (size_t x = 0; x < hi.length(); x++) {
    std::cout << hi[x] << "\n";
  }
  std::cout << "You entered: " << a << ", " << b << " and " << c << "\n";
  if (!hi.empty()) {
    std::cout << "Btw this is what you entered after: " << hi << endl;
  } else {
    cout << "No extra input provided!" << endl;
  }
}

void print_and_append() {
  char h1[100];
  printf("Enter your string (without spaces please): ");
  scanf("%99s", h1);
  for (size_t x = 0; x < strlen(h1); x++) {
    for (size_t y = 0; y <= x; y++) {
      printf("%c", h1[y]);
    }
    printf("\n");
  }
}

void listings() {
  int input = 0;
  printf("\nPlease enter a digit: ");
  int result{};
  int count = 0;
  result = scanf("%d", &input);
  for (int x = 0; x <= input; x++) {
    for (int y = 0; y <= input; y++) {
      printf("[%d], [%d]\n", x, y);
      count++;
    }
  }
  printf("Printed %d times", count);
}

void coffee_machine() {
  bool running{true};
  int current_water = 500;
  int current_coffee_beans = 1;
  // needed water for types of coffee brews
  const int cost_espresso_beans = 2;
  const int water_cost_of_espresso = 30;
  const int water_cost_of_americano = 180;
  const int water_cost_of_espresso_doppio = 50;
  string not_enough = "water";
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
        printf("Not enough %s.. Please refill.. (r)\n", not_enough.c_str());
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
    } else if (input == 'd') {
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

void loading_spinner() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(100, 300);
  const char spinchars[] = {'|', '/', '-', '\\'};
  const char *frames[] = {
      "[=           ]", "[==          ]", "[===         ]", "[====        ]",
      "[=====       ]", "[======      ]", "[=======     ]", "[========    ]",
      "[=========   ]", "[==========  ]", "[==========  ]", "[=========== ]",
      "[============]",
  };
  int i = 0;
  bool spinner{true};
  bool bar{false};

  int num_of_frames_bar = sizeof(frames) / sizeof(frames[0]);
  while (spinner) {
    if (i == 15) {
      spinner = false;
      bar = true;
      i = 0;
    }
    std::cout << "\r" << spinchars[i % 4] << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
  }
  i = 0;
  while (bar && i < num_of_frames_bar) {
    int random_number = dist(gen);
    std::cout << "\r" << frames[i % num_of_frames_bar] << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(random_number));
    i++;
  }
  printf(
      "\nYou have seen a PoC for animations coded by NoJamesHere. Goodbye.\n");
}

void square_stairs() {
  printf("Square: \n\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 13; j++) {
      printf("#");
    }
    printf("\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  printf("\n\n Stairs:\n");
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  for (int i = 0; i < 15; i++) {
    for (int j = 0; j < i; j++) {
      printf("#");
    }
    printf("\n");
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
  }
}

void hello() {
  std::vector<std::string> phrases{
      "Any day could be a good day.", "Don't worry, I just pooped myself!",
      "bodos binted?", "Finally got the name right.."};
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dist(0, phrases.size() - 1);

  int random_number = dist(gen);
  std::cout << "\n\n\n" << phrases[random_number] << endl;
}

int main() {
  function1();
  listings();
  coffee_machine();
  loading_spinner();
  square_stairs();
  hello();
  return 0;
}
