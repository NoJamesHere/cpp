#include <chrono>
#include <iostream>
#include <stdio.h>
#include <string>
#include <thread>
int function(int a, int b) {
  int count{};
  for (int i = 0; i < a + 1; i++) {
    for (int j = 0; j < b + 1; j++) {
      printf("[OUTPUT:] %d, %d \n", i, j);
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
      count++;
    }
  }
  return count;
}

int how_much_output(int a) {
  std::string end = "Wow";
  char frames[] = {'/', '|', '-', '\\'};
  if (a < 5 && a > 1) {
    end = "Not so impressive..";
  } else if (a > 5 && a < 15) {
    end = "Hm okay..";
  } else if (a > 15 && a < 25) {
    end = "Oh okay!";
  } else if (a > 25 && a < 50) {
    end = "WOW!";
  } else if (a > 50) {
    end = "WHAT THE F@!K??";
  } else if (a == 1) {
    printf("\n\nSeriously?? You only have one.. Printed only, ONE array.");
    return 0;
  }

  int i = 0;
  printf("\n");
  while (i <= 15) {
    std::cout << "\r" << frames[i % 4] << std::flush;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    i++;
  }
  std::cout << "\rYour Terminal Has Been Arrayed!\n" << std::endl;
  printf("\n\n%s You have %d OUTPUT(S) in total!", end.c_str(), a);
  return 0;
}

int main() {
  int variable_1 = 0;
  int variable_2 = 0;
  printf("Your first number please!: ");
  scanf("%d", &variable_1);

  printf("\nYour second number please!: ");
  scanf("%d", &variable_2);
  int count = function(variable_1, variable_2);
  how_much_output(count);
  return 0;
}
