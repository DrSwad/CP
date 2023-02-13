#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> s(n);
  for (string &i : s) cin >> i;

  vector<bool> vis(26, false);
  for (string i : s) vis[i[0] - 'A'] = true;

  for (string i : s) {
    bool flag = true;
    for (char c : i) {
      if (!vis[c - 'A']) {
        flag = false;
      }
    }
    if (flag) {
      cout << "Y\n";
      return 0;
    }
  }

  cout << "N\n";

  return 0;
}