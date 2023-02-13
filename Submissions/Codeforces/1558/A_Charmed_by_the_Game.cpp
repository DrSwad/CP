#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int a, b;
  scanf("%d %d", &a, &b);

  int n = a + b;
  vector<bool> vis(n + 1, false);

  int x = n / 2;
  int y = (n + 1) / 2;
  for (int a0 = 0; a0 <= min(x, a); a0++) {
    int b0 = y - (a - a0);
    if (b0<0 or b0> b) continue;
    vis[a0 + b0] = true;
  }

  swap(x, y);
  for (int a0 = 0; a0 <= min(x, a); a0++) {
    int b0 = y - (a - a0);
    if (b0<0 or b0> b) continue;
    vis[a0 + b0] = true;
  }

  vector<int> ans;
  for (int i = 0; i <= a + b; i++) {
    if (vis[i]) ans.push_back(i);
  }

  printf("%d\n", ans.size());
  for (int i = 0; i < ans.size(); i++) {
    if (i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    test_case();
  }

  return 0;
}