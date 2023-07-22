#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<string> a(n);
  for (auto &s : a) cin >> s;
  a.insert(a.begin(), "");

  vector<int> init_len(n + 1);
  for (int i = 0; i <= n; i++) {
    init_len[i] = a[i].length();
  }

  auto greater_possible =
    [&](int i, int j) {
      assert(a[i].length() == a[i - 1].length());
      int len = a[i].length();
      if (j >= len) return false;
      string prv = a[i - 1].substr(j);
      string cur = a[i].substr(j);
      for (char &c : cur) if (c == '?') c = '9';
      return cur > prv;
    };

  auto fill_zero =
    [&](int i) {
      for (char &c : a[i]) {
        if (c == '?') {
          c = '0';
        }
      }
    };

  auto no =
    [&]() {
      cout << "NO\n";
      exit(EXIT_SUCCESS);
    };

  for (int i = 1; i <= n; i++) {
    if (a[i][0] == '0') no();
    if (init_len[i] < init_len[i - 1]) no();
  }

  for (int i = 1; i <= n; i++) {
    if (init_len[i] > init_len[i - 1]) {
      if (a[i][0] == '?') a[i][0] = '1';
      fill_zero(i);
    }
    else {
      int len = a[i].length();
      for (int j = 0; j < len; j++) {
        if (a[i][j] != '?') {
          if (a[i][j] < a[i - 1][j]) no();
          else if (a[i][j] > a[i - 1][j]) {
            fill_zero(i);
            break;
          }
          else if (!greater_possible(i, j + 1)) no();
        }
        else {
          if (greater_possible(i, j + 1)) {
            a[i][j] = a[i - 1][j];
          }
          else {
            if (a[i - 1][j] == '9') no();
            else {
              a[i][j] = a[i - 1][j] + 1;
              fill_zero(i);
              break;
            }
          }
        }
      }
    }
  }

  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    cout << a[i] << "\n";
  }

  return 0;
}