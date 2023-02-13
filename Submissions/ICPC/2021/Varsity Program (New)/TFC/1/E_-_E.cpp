#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e7 + 5;

int sm[N];
ll sm_dp[N];
ll dp[N];
ll ans[N];
bool is_composite[N];
vector<int> primes;

void init() {
  dp[1] = 1;
  for (int i = 2; i < N; i++) {
    if (!is_composite[i]) {
      primes.push_back(i);
      sm[i] = i;
      sm_dp[i] = 1 + sm[i];
    }
    for (int j = 0; j < primes.size() and i * primes[j] < N; j++) {
      int num = i * primes[j];
      is_composite[num] = true;
      if (i % primes[j] == 0) {
        sm[num] = sm[num / primes[j]] * primes[j];
        sm_dp[num] = sm_dp[num / primes[j]] + sm[num];
      }
      else {
        sm[num] = primes[j];
        sm_dp[num] = 1 + sm[num];
      }
    }

    dp[i] = dp[i / sm[i]] * sm_dp[i];
    ans[i] = ans[i - 1] + dp[i];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n;
  while (true) {
    cin >> n;
    if (!n) break;
    cout << ans[n] << "\n";
  }

  return 0;
}