#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;

  int cnt[2] = {0};
  while (n--) {
    int x, y;
    scanf("%d %d", &x, &y);
    cnt[x > 0]++;
  }

  puts(cnt[0] <= 1 or cnt[1] <= 1 ? "Yes" : "No");

  return 0;
}