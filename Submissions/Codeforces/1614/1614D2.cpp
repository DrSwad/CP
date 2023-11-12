#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int A = 2e7 + 5;

int n;
int a[N];

vector<int> prime;
bool is_composite[A];
int min_divisor[A];

void find_min_divisors() {
  min_divisor[1] = 1;
  for (int i = 2; i < A; i++) {
    if (!is_composite[i]) {
      prime.push_back(i);
      min_divisor[i] = i;
    }
    for (int j = 0; j < prime.size() && i * prime[j] < A; j++) {
      is_composite[i * prime[j]] = true;
      min_divisor[i * prime[j]] = prime[j];
      if (i % prime[j] == 0) break;
    }
  }
}

int tot_divisors;
int divisors[N];

void find_divisors(int num) {
  if (num == 1) return;

  int p = min_divisor[num];
  int pp = p;
  int prv_tot_divisors = tot_divisors;

  while (num % p == 0) {
    for (int i = 1; i <= prv_tot_divisors; i++) {
      divisors[++tot_divisors] = pp * divisors[i];
    }
    num /= p;
    pp *= p;
  }

  find_divisors(num);
}

int multiples[A];
long long dp[A];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  find_min_divisors();

  cin >> n;
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= n; i++) {
    tot_divisors = 1;
    divisors[1] = 1;
    find_divisors(a[i]);

    for (int j = 1; j <= tot_divisors; j++) {
      multiples[divisors[j]]++;
    }
  }

  for (int i = A - 1; i >= 1; i--) {
    dp[i] = 1ll * i * multiples[i];

    for (int j = 0; j < prime.size() and i * prime[j] < A; j++) {
      int k = i * prime[j];
      dp[i] = max(dp[i], dp[k] + 1ll * i * (multiples[i] - multiples[k]));
    }
  }

  cout << dp[1] << "\n";

  return 0;
}