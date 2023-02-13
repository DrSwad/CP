#include <bits/stdc++.h>
using namespace std;

const int N = 200000 + 5;

vector<int> prime;
vector<bool> is_composite(N, false);
vector<int> mu(N);
vector<vector<int>> divs(N);
int n, q;
vector<int> a, freq(N, 0), cnt(N, 0);

void sieve(int n) {
  mu[1] = 1;

  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      mu[i] = -1;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < n; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) { // prime[j] divides i
        mu[i * prime[j]] = 0;
        break;
      }
      else { // prime[j] does not divide i
        mu[i * prime[j]] = mu[i] * mu[prime[j]];
      }
    }
  }
}

void init() {
  sieve(N);

  for (int d = 1; d < N; d++) {
    if (!mu[d]) continue;
    for (int m = d; m < N; m += d) {
      divs[m].push_back(d);
      cnt[d] += freq[m];
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q;
  a.resize(n);
  for (int &i : a) cin >> i, freq[i]++;

  init();

  while (q--) {
    int x;
    cin >> x;

    long long ans = 0;
    for (int d : divs[x]) {
      ans += mu[d] * cnt[d];
    }

    cout << ans << "\n";
  }

  return 0;
}