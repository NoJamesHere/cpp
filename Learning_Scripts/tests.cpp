#include <iostream>
#include <stdio.h>
#include <string.h>
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
  printf("Enter your string: ");
  scanf("%99s", h1);
  for (size_t x = 0; x < strlen(h1); x++) {
    for (size_t y = 0; y <= x; y++) {
      printf("%c", h1[y]);
    }
    printf("\n");
  }
  return 0;
}

int main() {
  print_and_append();
  return 0;
}
