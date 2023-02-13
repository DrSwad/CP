#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i, i--;

  string s(m, 'B');

  for (int i = 0; i < n; i++) {
    int pos1 = a[i], pos2 = m - 1 - a[i];
    if (pos1 > pos2) swap(pos1, pos2);
    if (s[pos1] != 'A') s[pos1] = 'A';
    else s[pos2] = 'A';
  }

  cout << s << "\n";
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