#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string s;
  cin >> s;

  vector<int> states(1, 1);
  for (char c : s) {
    if (c == '+') {
      if (states.size() == 1) {
        states.push_back(1);
      }
      else {
        states.push_back(-1);
      }
    }
    else if (c == '-') {
      assert(!states.empty());
      states.pop_back();
    }
    else if (c == '0') {
      if (states.back() == 1) {
        cout << "NO\n";
        return;
      }
      states.back() = 0;
    }
    else if (c == '1') {
      int i;
      for (i = (int)states.size() - 1; i >= 0 and states[i] == -1; i--) {
        states[i] = 1;
      }
      if (states[i] == 0) {
        cout << "NO\n";
        return;
      }
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