#include <bits/stdc++.h>
using namespace std;

void test_case() {}

int ans[1005][1005];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  scanf("%d", &n);
  int ar[n + 5];
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &ar[i]);
  }
  memset(ans, 0, sizeof ans);
  for (int i = 0; i < (2 * n - 1); i++)
  {
    for (int j = 0; j < (2 * n - 1); j++)
    {
      ans[i][j] = ar[(i + j) % n];
    }
  }
  printf("%d\n", 2 * n - 1);
  for (int i = 0; i < 2 * n - 1; i++)
  {
    for (int j = 0; j < 2 * n - 1; j++)
    {
      printf("%d", ans[i][j]);
      if (j < 2 * n - 1) printf(" ");
    }
    puts("");
  }
  return 0;
}