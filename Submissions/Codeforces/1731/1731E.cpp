#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e6 + 5;
vector<int> prime;
bool is_composite[N];
int phi[N];
ll coprime_pairs[N];

void sieve(int n = N) {
  fill(is_composite, is_composite + n, false);
  phi[1] = 1;

  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      phi[i] = i - 1;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < n; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) {
        phi[i * prime[j]] = phi[i] * prime[j];
        break;
      }
      else {
        phi[i * prime[j]] = phi[i] * phi[prime[j]];
      }
    }
  }

  coprime_pairs[1] = 0;
  for (int i = 2; i < n; i++) {
    coprime_pairs[i] = coprime_pairs[i - 1] + phi[i];
  }
}

void test_case() {
  int n;
  ll m;
  cin >> n >> m;

  vector<ll> freq(n, 0);
  for (int g = 2; g <= n; g++) {
    freq[g - 1] = coprime_pairs[n / g] / (g - 1);
  }

  ll ans = m;
  for (int w = n - 1; w > 0 and m > 0; w--) {
    ll take = min(freq[w], m / w);
    ans += take;
    m -= 1ll * w * take;
  }

  if (m > 0) cout << "-1\n";
  else cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}