#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    a[i]++;
  }
  reverse(a.begin() + 1, a.end());

  vector<int> jumps(n + 1, -1);
  jumps[0] = 0;
  for (int i = 1; i <= n; i++) {
    if (i - a[i] >= 0 and jumps[i - a[i]] >= 0) {
      jumps[i] = jumps[i - a[i]] + 1;
    }
  }

  vector<int> max_jumps(n + 1);
  max_jumps[0] = 0;
  for (int i = 1, mx = 0; i <= n; i++) {
    mx = max(mx, jumps[i]);
    max_jumps[i] = max(max_jumps[i], mx + 1);
    if (i - a[i] >= 0) {
      max_jumps[i] = max(max_jumps[i], max_jumps[i - a[i]] + 1);
    }
  }

  for (int i = n; i >= 2; i--) {
    if (i < n) cout << " ";
    if (jumps[i - 1] == a[i] - 1) cout << "0";
    else if (jumps[i - 1] >= 0 or max_jumps[i - 1] >= a[i] - 1) cout << "1";
    else cout << "2";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}