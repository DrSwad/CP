#include <bits/stdc++.h>
using namespace std;

const int L = 8;

int dist(string s1, string s2) {
  int diff = 0;
  for (int i = 0; i < L; i++) {
    diff += s1[i] != s2[i];
  }
  return min(diff, 3);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int q, n;
  cin >> q >> n;

  vector<string> ns(n);
  for (string &s : ns) cin >> s;

  while (q--) {
    string qs;
    int d;
    cin >> qs >> d;

    int ans = 0;
    for (int i = 0; i < n; i++) {
      ans += dist(ns[i], qs) == d;
    }

    cout << ans << "\n";
  }

  return 0;
}