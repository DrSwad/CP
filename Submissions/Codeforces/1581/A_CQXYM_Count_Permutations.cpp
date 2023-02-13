#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int MOD = 1e9 + 7;

int fact[N];

void test_case() {
  int n;
  cin >> n;

  cout << (long long)fact[2 * n] * (MOD + 1) / 2 % MOD << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  fact[0] = 1;
  for (int i = 1; i < N; i++)
    fact[i] = (long long)fact[i - 1] * i % MOD;


  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}