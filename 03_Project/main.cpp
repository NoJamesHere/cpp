#include <stdio.h>

// I wanted to use printf instead of std::

// This is set into a function, so it can be reused at any given point
int hello(int a, int b) { return a + b; }

int main() {
  int value1 = 0;
  int value2 = 0;
  int result = 0;
  printf("what is your first value?: ");

  result = scanf("%d", &value1);
  while (result != 1) {
    printf("This is not a valid input. Try again..: ");

    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    result = scanf("%d", &value1);
  }
  printf("\nSecond value?: ");
  result = scanf("%d", &value2);

  while (result != 1) {
    printf("This is not a valid input.. Try again!: ");

    int c = 0;
    while ((c = getchar()) != '\n' && c != EOF) {
    }
    result = scanf("%d", &value2);
  }

  int sum = hello(value1, value2);
  printf("You entered: %d\n", sum);
  return 0;
}
