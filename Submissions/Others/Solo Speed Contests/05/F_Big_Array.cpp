#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  long long k;
  cin >> n >> k;

  vector<pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    int a, b;
    cin >> a >> b;
    v.push_back({a, b});
  }

  sort(v.begin(), v.end());

  int at = -1, i = 0;
  while (k) {
    auto [a, b] = v[i++];
    at = a;
    k = max(0ll, k - b);
  }

  cout << at << endl;

  return 0;
}