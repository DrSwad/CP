#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 5;

int n;
ll k;
int a[N];
int pfreq[N];
ll psum[N];
ll need[N];

void sieve() {
  for (int d = 1; d < N; d++) {
    for (int u = d; u < N + d; u += d) {
      int l = u - d;
      int uu = min(N - 1, u - 1);
      int f = pfreq[uu] - pfreq[l];
      ll sum = psum[uu] - psum[l];
      need[d] += (ll)f * u - sum;
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    pfreq[a[i]]++;
    psum[a[i]] += a[i];
  }

  for (int i = 1; i < N; i++) {
    pfreq[i] += pfreq[i - 1];
    psum[i] += psum[i - 1];
  }

  sieve();

  ll ans = 0;
  for (int d = 1; d < N; d++) {
    if (need[d] <= k) ans = d;
  }

  ll rem = k - ((ll)N * n - psum[N - 1]);
  if (rem >= 0) {
    ans = N + rem / n;
  }

  assert(ans > 0);

  cout << ans << "\n";

  return 0;
}