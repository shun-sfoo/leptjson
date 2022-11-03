#include <stdlib.h>

void mystery(int n);

int main() {
  mystery(0);
  mystery(50);
  mystery(100);
}

void mystery(int n) {
  n += 5;
  n /= 10;
  printf("%s\n", "**********" + 10 - n);
}
