#include <bits/stdc++.h>
using namespace std;

int mod;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k >> mod;

  int all = 1;
  for (int i = 0; i < n; i++) {
    all = mul(all, k);
  }

  for (int sum = 0; sum < k; sum++) {
    vector<int> digits;
    for (int d = 0; d < k; d++) {
      if (2 * d % k != sum) {
        digits.push_back(d);
      }
    }

    vector<int> ways(k, 0);
    ways[0] = 1;
    for (int i = 0; i < n; i++) {
      vector<int> nways(k, 0);
      for (int sum = 0; sum < k; sum++) {
        for (int d : digits) {
          int nsum = (sum + d) % k;
          nways[nsum] = add(nways[nsum], ways[sum]);
        }
      }
      swap(ways, nways);
    }

    all = add(all, mod - ways[sum]);
  }

  cout << all << "\n";

  return 0;
}