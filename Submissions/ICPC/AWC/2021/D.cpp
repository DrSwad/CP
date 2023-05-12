#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  string s;
  cin >> n >> s;

  vector<int> nxt(26, -1);
  int m;
  cin >> m;
  while (m--) {
    char b, c;
    cin >> b >> c;
    nxt[b - 'A'] = c - 'A';
  }

  int last = -1;
  for (int i = 0; i < n; i++) {
    int c = s[i] - 'A';
    if (last != -1 and nxt[last] != -1 and nxt[last] != c) {
      cout << "NO\n";
      return;
    }
    last = c;
  }

  if (nxt[last] != -1) cout << "NO\n";
  else cout << "YES\n";
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