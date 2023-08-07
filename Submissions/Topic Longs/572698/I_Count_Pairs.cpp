#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, p, k;
  cin >> n >> p >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 0;
  map<int, int> freq;
  for (int i : a) {
    int val = 1ll * i * i % p * i % p * i % p - 1ll * i * k % p;
    if (val < 0) val += p;
    ans += freq[val];
    freq[val]++;
  }

  cout << ans << "\n";

  return 0;
}