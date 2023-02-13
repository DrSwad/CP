#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  int cycles = 0;
  vector<int> cycle_id(n, -1);
  for (int i = 0; i < n; i++) {
    if (cycle_id[i] == -1) {
      int at = i;
      do {
        cycle_id[at] = cycles;
        at = p[at];
      } while (at != i);

      cycles++;
    }
  }

  int moves = n - cycles;
  for (int i = 0; i < n - 1; i++) {
    if (cycle_id[i] == cycle_id[i + 1]) {
      cout << moves - 1 << "\n";
      return;
    }
  }
  cout << moves + 1 << "\n";
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