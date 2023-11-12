#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;
  int n = s.size();

  set<int> pos;
  for (int i = 0; i < n; i++) pos.insert(i);
  pos.insert(n);

  set<int> abc;
  for (int i = 0; i + 3 <= n; i++) {
    if (s.substr(i, 3) == "ABC") {
      abc.insert(i);
    }
  }

  while (!abc.empty()) {
    int at = *abc.begin();
    abc.erase(at);
    for (int i = 0; i < 3; i++) {
      pos.erase(at);
      at = *pos.upper_bound(at);
    }

    auto it = pos.lower_bound(at);
    for (int _ = 0; _ < 2; _++) {
      if (it == pos.begin()) break;
      it--;

      auto it2 = it;
      bool okay = true;
      for (int i = 0; i < 3; i++, it2++) {
        if (*it2 >= n or s[*it2] != 'A' + i) {
          okay = false;
          break;
        }
      }

      if (okay) abc.insert(*it);
    }
  }

  for (int i : pos) if (i < n) cout << s[i];
  cout << "\n";

  return 0;
}