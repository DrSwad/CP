#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  set<int> excepts;
  bool except_state = true;
  for (int i = 0; i < n; i++) {
    if (s[i] < 'a' or 'z' < s[i]) s[i] = 'a' + s[i] - 'A';
    if ('A' <= s[i] and s[i] <= 'Z') excepts.insert(i);
  }

  int q;
  cin >> q;

  while (q--) {
    int type;
    int i;
    char c;
    cin >> type >> i >> c;

    if (type == 1) {
      i--;

      excepts.erase(i);
      if (('A' <= c and c <= 'Z') == except_state) excepts.insert(i);

      if (c < 'a' or 'z' < c) c = 'a' + c - 'A';
      s[i] = c;
    }
    else if (type == 2) excepts.clear(), except_state = true;
    else excepts.clear(), except_state = false;
  }

  for (int i = 0; i < n; i++) {
    bool upper = (except_state == true and excepts.find(i) != excepts.end()) or
                 (except_state == false and excepts.find(i) == excepts.end());
    cout << (char)((upper ? 'A' : 'a') + s[i] - 'a');
  }
  cout << "\n";

  return 0;
}