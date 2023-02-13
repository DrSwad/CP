#include <bits/stdc++.h>
using namespace std;

const int C = 26;

template<typename T>
vector<int> prefix_function(int n, const T &s) {
  vector<int> p(n, 0);
  int k = 0;
  for (int i = 1; i < n; i++) {
    while (k > 0 && !(s[i] == s[k])) {
      k = p[k - 1];
    }
    if (s[i] == s[k]) {
      k++;
    }
    p[i] = k;
  }
  return p;
}
template<typename T>
vector<int> prefix_function(const T &s) {
  return prefix_function((int) s.size(), s);
}

template<typename T>
vector<vector<int>> prefix_function_automaton(const T &s, int alphabet_size, int smallest_alphabet) {
  int n = s.size();
  vector<int> pf = prefix_function(s);
  vector<vector<int>> automaton(n + 1, vector<int>(alphabet_size));
  for (int i = 0; i <= n; i++) {
    for (int c = 0; c < alphabet_size; c++) {
      if (i < n and s[i] == smallest_alphabet + c) {
        automaton[i][c] = i + 1;
      }
      else {
        automaton[i][c] = i == 0 ? 0 : automaton[pf[i - 1]][c];
      }
    }
  }
  return automaton;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string t, s;
  cin >> t >> s;
  int ns = s.length(), nt = t.length();

  vector<vector<int>> automaton = prefix_function_automaton(s, C, 'a');

  vector<int> dp(ns + 1, 0);
  dp[ns] = 1;

  for (int it = nt - 1; it >= 0; it--) {
    char ch = t[it];
    vector<int> ndp(ns + 1, 0);

    for (int i = 0; i <= ns; i++) {
      for (int c = 0; c < C; c++) {
        if (ch != '?' and c != ch - 'a') continue;
        ndp[i] = max(ndp[i], (i == ns) + dp[automaton[i][c]]);
      }
    }

    swap(dp, ndp);
  }

  cout << dp[0] << "\n";

  return 0;
}