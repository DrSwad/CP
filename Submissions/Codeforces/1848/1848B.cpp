#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  // 7 3
  // 0 1 2 2 2 1 0
  // c[0] = {0, 6}, {0, 2, 2, 0}, ans = 2
  // c[1] = {1, 5}, {1, 1, 1, 1}, ans = 1
  // c[2] = {2, 3, 4}, {2, 0, 0, 1, 0}, ans = 2
  vector<vector<int>> c_pos(k);
  for (int i = 0; i < n; i++) {
    int c;
    cin >> c;
    c--;
    c_pos[c].push_back(i);
  }
  for (int c = 0; c < k; c++) {
    c_pos[c].push_back(n);
  }

  // O(n + k)
  function<bool(int)> check =
    [&](int max_steps) {
      for (int c = 0; c < k; c++) {
        if (c_pos[c].empty()) continue;
        bool okay = true;
        int last = -1;
        bool recolored = false;
        for (int at : c_pos[c]) {
          int steps = at - last - 1;
          if (steps > max_steps) {
            if (recolored) {
              okay = false;
              break;
            }
            else {
              if (steps > 2 * max_steps + 1) {
                okay = false;
                break;
              }
              recolored = true;
            }
          }
          last = at;
        }
        if (okay) return true;
      }
      return false;
    };

  // O(logn)
  int L = -1, R = n;
  while (R - L > 1) {
    int max_steps = (L + R) / 2;
    if (check(max_steps)) R = max_steps;
    else L = max_steps;
  }

  // O(logn * (n + k))

  cout << R << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}