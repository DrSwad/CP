#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int K = 100;
const int N = 1e7;

ll n;
int k;
int a[K];
ll divs[N], dp[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 0; i < k; i++) {
    cin >> a[i];
  }
  sort(a, a + k, greater<int>());

  int sz = 0;
  for (ll l = 1; l <= n; ) {
    ll d = n / l;
    divs[sz++] = d;
    l = n / d + 1;
  }
  divs[sz++] = 0;

  for (int i = 0; i < k; i++) {
    for (int j = 0, ptr = 0; j < sz; j++) {
      ll d = divs[j] / a[i];
      while (ptr<sz and divs [ptr]> d) ptr++;
      dp[j] += d - dp[ptr];
    }
  }

  cout << n - dp[0] << "\n";

  return 0;
}