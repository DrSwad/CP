#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  const int len = 8;
  vector<string> a(n);
  for (auto &s : a) cin >> s;
  a.insert(a.begin(), string(len, '0'));

  vector<int> init_len(n + 1);
  init_len[0] = 0;
  for (int i = 1; i <= n; i++) {
    init_len[i] = a[i].length();
  }

  for (auto &s : a) {
    if (s.length() < len) {
      s = string(len - s.length(), '0') + s;
    }
  }

  auto greater_possible =
    [&](int i, int j) {
      if (j + 1 >= len) return false;
      string prv = a[i - 1].substr(j + 1);
      string cur = a[i].substr(j + 1);
      return cur > prv;
    };

  auto fill_rest =
    [&](int i, int j) {
      for (int k = j; k < len; k++) {
        if (a[i][k] == '?') {
          a[i][k] = '0';
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
    if (init_len[i] > init_len[i - 1]) {}

    for (int j = 0; j < len; j++) {
      if (a[i][j] != '?') {
        if (a[i][j] < a[i - 1][j]) no();
        else if (a[i][j] > a[i - 1][j]) {
          fill_rest(i, j);
          break;
        }
      }
      else {
        if (greater_possible(i, j)) {
          a[i][j] = a[i - 1][j];
          if (a[i - 1][j] == '0' and j >= nonzero[i]) {
            bool found = false;
            for (int k = 0; k <= nonzero[i]; k++) {
              if (a[i][k] != '0') {
                found = true;
                break;
              }
            }

            if (!found) {
              a[i][j] = '1';
              for (int k = j + 1; k < len; k++) {
                if (a[i][k] == '?') a[i][k] = '0';
              }
              break;
            }
          }
        }
        else {
          if (a[i - 1][j] == '9') no();
          else {
            a[i][j] = a[i - 1][j] + 1;
            fill_rest(i, j);
            break;
          }
        }
      }
    }
    if (a[i] <= a[i - 1]) no();
  }

  for (int i = 1; i <= n; i++) {
    bool found = false;
    for (int j = 0; j <= nonzero[i]; j++) {
      if (a[i][j] != '0') {
        found = true;
        break;
      }
    }
    if (!found) {
      cout << "NO\n";
      return;
    }
  }

  cout << "YES\n";
  for (int i = 1; i <= n; i++) {
    bool flag = false;
    for (int j = 0; j < len; j++) {
      if (a[i][j] != '0') {
        flag = true;
        cout << a[i][j];
      }
      else if (flag) cout << a[i][j];
    }
    cout << "\n";
  }

  return 0;
}