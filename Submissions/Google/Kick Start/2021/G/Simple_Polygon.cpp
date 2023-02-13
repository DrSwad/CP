#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, a;
  cin >> n >> a;

  a += 2;
  if (a < n) {
    cout << "IMPOSSIBLE\n";
    return;
  }

  cout << "POSSIBLE\n";
  a -= n;

  vector<pair<int, int>> p(n);
  int yy[] = {1, 2, 1, 0};
  for (int i = 0; i < n; i++) {
    auto & [x, y] = p[i];
    x = i / 2;
    y = yy[i % 4];
  }

  p[1].second += a;

  if (n == 3) {
    for (int i = 0; i < n; i++) {
      p[i].second--;
    }
  }

  for (int i = 0; i < n; i++) {
    int r = i % 4;
    if (r == 1 or r == 2) {
      cout << p[i].first << " " << p[i].second << "\n";
    }
  }
  for (int i = n - 1; i >= 0; i--) {
    int r = i % 4;
    if (r == 0 or r == 3) {
      cout << p[i].first << " " << p[i].second << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}