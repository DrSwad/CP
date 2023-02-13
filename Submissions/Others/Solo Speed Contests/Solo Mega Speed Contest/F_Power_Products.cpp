#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, k;
int a[N];
vector<pair<int, int>> pfact[N];

bool composite[N];
void sieve() {
  for (int p = 2; p < N; p++) {
    if (!composite[p]) {
      for (int num = p; num < N; num += p) {
        composite[num] = true;
        int exp = 0;
        int _num = num;
        while (_num % p == 0) {
          _num /= p;
          exp++;
        }
        pfact[num].push_back({p, exp});
      }
    }
  }
}

int main() {
  cin >> n >> k;
  for (int i = 1; i <= n; i++) scanf("%d", &a[i]);

  sieve();
  for (int i = 1; i < N; i++) {
    auto tmp = pfact[i];
    pfact[i].clear();
    for (auto & [p, exp] : tmp) {
      exp %= k;
      if (exp) pfact[i].push_back({p, exp});
    }
  }

  map<vector<pair<int, int>>, int> mp;
  long long ans = 0;

  for (int i = 1; i <= n; i++) {
    if (mp.find(pfact[a[i]]) != mp.end()) {
      ans += mp[pfact[a[i]]];
    }

    auto tmp = pfact[a[i]];
    vector<pair<int, int>> ipfact;
    for (auto & [p, exp] : tmp) {
      exp = (k - exp) % k;
      if (exp) ipfact.push_back({p, exp});
    }
    mp[ipfact]++;
  }

  cout << ans << endl;

  return 0;
}