#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  vector<string> c(n);
  for (string &s : c) cin >> s;

  vector<string> d(m);
  for (string &s : d) cin >> s;

  int p0;
  cin >> p0;

  map<string, int> price;
  for (int i = 0; i < m; i++) {
    int p;
    cin >> p;
    price[d[i]] = p;
  }

  int ans = 0;
  for (string s : c) {
    if (!price.count(s)) ans += p0;
    else ans += price[s];
  }

  cout << ans << "\n";

  return 0;
}