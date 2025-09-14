#include <stdio.h>

int main() {
  while (true) {
    for (int i = 0; i < 20; i++) {
      for (int j = 1; j < 20; j++) {
        for (int h = 2; h < 20; h++) {
          printf("%d, ", i * h * j);
        }
      }
    }
  }
  return 0;
}
