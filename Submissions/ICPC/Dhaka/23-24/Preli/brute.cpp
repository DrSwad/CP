#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<string> grid(n);
  for (string &row : grid) cin >> row;

  string s;
  for (string row : grid) {
    for (int it1 = 0; it1 < k; it1++) {
      for (char cell : row) {
        for (int it2 = 0; it2 < k; it2++) {
          s += cell;
        }
      }
    }
  }

  int q;
  cin >> q;

  int len = s.length();
  assert(len == n * n * k * k);

  vector<int> pref(1, 0);
  for (int i = 0; i < len; i++) {
    pref.push_back(pref.back() + (s[i] == '1'));
  }

  while (q--) {
    int l, r;
    cin >> l >> r;
    cout << (pref[r + 1] - pref[l]) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case " << cs << ":\n";
    test_case();
  }

  return 0;
}