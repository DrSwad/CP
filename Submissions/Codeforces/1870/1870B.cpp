#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b(m);
  for (int &i : b) cin >> i;

  int bb = 0;
  for (int i : b) bb |= i;

  int x = 0;
  for (int i : a) x ^= i;

  int y = 0;
  for (int i : a) y ^= (i | bb);

  if (y < x) swap(x, y);

  cout << x << " " << y << "\n";
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