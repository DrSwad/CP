#include <bits/stdc++.h>
using namespace std;

int n, l, r;
string s;
set<string> reachable;

void dfs(string s) {
  reachable.insert(s);
  for (int i = 0; i + l < n; i++) {
    for (int j = i + l; j <= i + r and j < n; j++) {
      swap(s[i], s[j]);
      if (reachable.find(s) == reachable.end()) {
        dfs(s);
      }
      swap(s[i], s[j]);
    }
  }
}

int main() {
  cin >> n >> l >> r >> s;
  dfs(s);
  cout << *reachable.begin() << endl;

  return 0;
}