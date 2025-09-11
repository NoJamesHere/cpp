#include <chrono>
#include <iostream>
#include <random>
#include <stdio.h>
#include <string.h>
#include <thread>

using namespace std;

int function1() {
  int a, b, c{};
  string hi = "";
  std::cout << "Please enter three values: ";
  std::cin >> a >> b >> c >> hi;

  for (size_t x = 0; x < hi.length(); x++) {
    std::cout << hi[x] << "\n";
  }
  std::cout << "You entered: " << a << ", " << b << " and " << c << "\n";
  std::cout << "Btw this is what you entered after: " << hi;
  return 0;
}

int print_and_append() {
  char h1[100];
  printf("Enter your string (without spaces please): ");
  scanf("%99s", h1);
  for (size_t x = 0; x < strlen(h1); x++) {
    for (size_t y = 0; y <= x; y++) {
      printf("%c", h1[y]);
    }
    printf("\n");
  }
  return 0;
}

int listings() {
  int input = 0;
  printf("Please enter a digit: ");
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
  return 0;
}

int coffee_machine() {
  int current_water = 500;
  bool running{true};
  // needed water for types of coffee brews
  const int water_cost_of_espresso = 30;
  const int water_cost_of_americano = 180;
  const int water_cost_of_espresso_doppio = 50;

  char input;
  printf("Enter 'q' to quit\n\n");
  while (running) {
    printf("\nCurrently the tank has %d ml of water. \n\n", current_water);
    printf("What coffee would you like?\n(e, a, d / espresso, americano, "
           "espresso doppio): ");
    scanf(" %c", &input);
    printf("\n");
    if (input == 'e') {
      if (current_water >= water_cost_of_espresso) {
        printf("Here you have your espresso. Enjoy!\n");
        current_water -= water_cost_of_espresso;
      } else {
        printf("Not enough water.. Please refill..\n");
      }
    } else if (input == 'a') {
      if (current_water >= water_cost_of_americano) {
        printf("Here you have your americano. Enjoy!\n");
        current_water -= water_cost_of_americano;
      } else {
        printf("Not enough water.. Please refill..\n");
      }
    } else if (input == 'd') {
      if (current_water >= water_cost_of_espresso_doppio) {
        printf("Here you have your espresso doppio. Enjoy!\n");
        current_water -= water_cost_of_espresso_doppio;
      } else {
        printf("Not enough water.. Please refill...\n");
      }
    } else if (input == 'r') {
      current_water = 500;
      printf("Refilled your water! Tank's now full! (%d ml)\n\n",
             current_water);

    } else if (input == 'q') {
      running = false;
    } else {
      printf("Your input '%c' is not a valid option.\n", input);
    }
  }
  return 0;
}

int loading_spinner() {
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
  return 0;
}

int square_stairs() {
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
  return 0;
}
int main() {
  function1();
  listings();
  coffee_machine();
  loading_spinner();
  square_stairs();
  return 0;
}
