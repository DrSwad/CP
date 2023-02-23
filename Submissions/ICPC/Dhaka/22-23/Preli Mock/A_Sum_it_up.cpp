#include <stdio.h>
int main() {
  int x, y, z, sum;
  scanf("%d %d %d", &x, &y, &z);
  sum = x + y + z;

  printf("Sum of %d, %d and %d is %d\n", x, y, z, sum);

  return 0;
}