#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;

bool ans[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int k = 2; k < N; k++) {
    ll sum = 1ll * k * k + k + 1;
    ll term = 1ll * k * k;
    while (sum < N) {
      ans[sum] = true;
      term *= k;
      sum += term;
    }
  }

  for (int cs = 1; cs <= t; cs++) {
    int n;
    cin >> n;
    if (ans[n]) cout << "YES\n";
    else cout << "NO\n";
  }

  return 0;
}