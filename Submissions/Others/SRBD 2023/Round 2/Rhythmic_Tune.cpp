#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> z_function(int n, const T &s) {
  vector<int> z(n, n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    z[i] = (i > r ? 0 : min(r - i + 1, z[i - l]));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

template<typename T>
vector<int> z_function(const T &s) {
  return z_function((int) s.size(), s);
}

void test_case() {
  string s;
  cin >> s;

  int ans = 0;

  int n = s.length();
  for (int i = 0; i < n; i++) {
    string ss = s.substr(i) + '$' + s.substr(i);
    auto z = z_function(ss);

    int st = n + 1 - i;
    for (int len = 1; st + len < (int)z.size(); len++) {
      int matches = z[st + len];
      int turns = matches / len;
      if (turns >= 1) {
        ans = max(ans, (turns + 1) * len);
      }
    }
  }

  cout << ans << "\n";
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