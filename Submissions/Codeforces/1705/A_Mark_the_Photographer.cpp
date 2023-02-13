#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  vector<int> h(2 * n);
  for (int &i : h) cin >> i;

  sort(h.begin(), h.end());

  for (int i = 0; i < n; i++) {
    if (h[i + n] - h[i] < x) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
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