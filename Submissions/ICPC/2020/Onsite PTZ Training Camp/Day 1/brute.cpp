#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  vector<int> q(n);
  for (int &i : q) cin >> i, i--;

  vector<int> ans(n);
  iota(ans.begin(), ans.end(), 0);

  int moves = 0;
  int mx_moves = 200;
  while (moves < mx_moves and p != ans) {
    vector<int> np(n);
    for (int i = 0; i < n; i++) {
      np[i] = q[p[i]];
    }
    moves++;
    swap(p, np);
  }

  cout << (moves < mx_moves ? moves : -1) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}