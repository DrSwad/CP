#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5;

vector<int> primes;
bool vis[N];
void sieve() {
  primes.push_back(2);
  for (int p = 3; p < N; p++) {
    if (p % 2 == 0) continue;
    if (!vis[p]) primes.push_back(p);

    for (ll q = (ll)p * p; q < N; q += p) {
      vis[q] = true;
    }
  }
}
bool is_prime(int x) {
  return (x == 2) or (x > 1 and x % 2 == 1 and !vis[x]);
}

void test_case() {
  int x;
  cin >> x;

  if (is_prime(x)) cout << "1\n";
  else if (is_prime(x + (x + 1))) cout << "2\n";
  else if (is_prime(x + (x - 1))) cout << "2\n";
  else {
    int ans1;
    if (x >= 0) ans1 = 2 * *lower_bound(primes.begin(), primes.end(), x);
    else ans1 = 2 * *upper_bound(primes.begin(), primes.end(), -x);

    int y = abs(2 * x - 2);
    int ans2 = *upper_bound(primes.begin(), primes.end(), y);

    cout << min(ans1, ans2) << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  sieve();

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}