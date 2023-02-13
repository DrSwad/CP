#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> last_pos(n + 1, n);
  for (int i = 0; i < n; i++) last_pos[a[i]] = i;

  int sorted_till;
  for (sorted_till = n - 2; sorted_till >= 0; sorted_till--) {
    if (a[sorted_till + 1] < a[sorted_till]) break;
  }
  sorted_till++;

  vector<bool> operated(n + 1, false);
  operated[0] = true;
  int last_zero = -1;
  int moves = 0;

  for (int i = 0; i < n; i++) {
    if (i <= last_zero or i < sorted_till) {
      if (!operated[a[i]]) operated[a[i]] = true, moves++;
      last_zero = max(last_zero, last_pos[a[i]]);
    }
    else break;
  }

  cout << moves << "\n";
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