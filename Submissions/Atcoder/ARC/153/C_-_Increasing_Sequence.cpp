#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> signs(n);
  for (int &i : signs) cin >> i;

  int si;
  for (si = 0; si < n - 1; si++) {
    if (signs[si] != signs[si + 1]) break;
  }

  vector<ll> ans(n);

  if (si == n - 1) {
    if (n % 2 == 0) cout << "No\n";
    else {
      ans.push_back(0);
      for (int i = 2; i < n; i += 2) {
        ans.push_back(i / 2);
        ans.push_back(-i / 2);
      }
      sort(ans.begin(), ans.end());
    }
  }
  else {
    iota(ans.begin(), ans.end(), 0ll);
    ll sum = 0;
    for (ll &i : ans) sum += i;

  }

  return 0;
}