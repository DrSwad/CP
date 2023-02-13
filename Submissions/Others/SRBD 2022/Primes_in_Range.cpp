#include <bits/stdc++.h>
using namespace std;

const int N = 1000000 + 5;

vector<int> prime;
vector<bool> is_composite(N, false);

void sieve(int n) {
  for (int i = 2; i < n; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
    }
    for (int j = 0; j < prime.size() && i * prime[j] < n; j++) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) { // prime[j] divides i
        break;
      }
    }
  }
}

void test_case() {
  int n, m;
  cin >> n >> m;
  cout << upper_bound(prime.begin(), prime.end(), m) - lower_bound(prime.begin(), prime.end(), n) << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  sieve(N);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}