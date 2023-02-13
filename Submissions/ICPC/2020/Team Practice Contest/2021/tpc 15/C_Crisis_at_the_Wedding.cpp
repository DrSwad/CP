#include <bits/stdc++.h>
using namespace std;

long long go(vector<int> g) {
  int n = g.size();
  long long cost = 0, carry = 0;

  long long total = 0;
  for (int i = 0; i < n; i++) total += g[i];
  long long each = total / n;

  for (int at = 0; at < n or carry; at++) {
    cost += carry;
    int _at = at >= n ? at - n : at;

    if (g[_at] > each) {
      carry += g[_at] - each;
      g[_at] = each;
    }

    if (g[_at] < each) {
      long long need = each - g[_at];
      long long take = min(carry, need);
      carry -= take;
      g[_at] += take;
    }
  }

  return cost;
}

int main() {
  int n;
  cin >> n;

  vector<int> g(n);
  for (int &i : g) scanf("%d", &i);

  vector<int> gi = g;
  reverse(gi.begin(), gi.end());

  cout << min(go(g), go(gi)) << endl;

  return 0;
}