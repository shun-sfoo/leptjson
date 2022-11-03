#include <stdio.h>

/* 10个台阶，每次只能上一个台阶或两个台阶，一共有多少种走法 */

int getways(int n);

int main() { printf("%d\n", getways(10)); }

int getways(int n) {
  if (n == 1 || n == 2) return n;

  int a = 1;
  int b = 2;
  int temp = 0;
  int i;
  for (i = 3; i <= n; i++) {
    temp = a + b;
    a = b;
    b = temp;
  }

  return temp;
}
