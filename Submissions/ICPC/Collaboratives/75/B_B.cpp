#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
int f[N];
void update(int p, int v) {
  while (p <= n) f[p] = max(f[p], v), p += p & -p;
}
int pref(int p) {
  int ret = 0;
  while (p) ret = max(ret, f[p]), p -= p & -p;
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;

  vector<pair<int, int>> v;
  for (int i = 1; i <= n; i++) {
    int a;
    cin >> a;
    v.emplace_back(a, i + 1 - a);
  }

  sort(v.begin(), v.end());

  for (auto [_, a] : v) {
    int dp = 1 + pref(a);
    update(a, dp);
  }

  cout << pref(n) << "\n";

  return 0;
}