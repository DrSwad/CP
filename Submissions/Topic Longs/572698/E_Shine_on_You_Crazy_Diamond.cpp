#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx_a = *max_element(a.begin(), a.end());
  vector<int> freq(mx_a + 1, 0);
  for (int i : a) freq[i]++;

  vector<int> primes, mul_cnt(mx_a + 1, 0);
  {
    vector<bool> vis(mx_a + 1, false);
    for (int i = 2; i <= mx_a; i++) {
      if (!vis[i]) primes.push_back(i);
      for (int j = i; j <= mx_a; j += i) {
        mul_cnt[i] += freq[j];
        vis[j] = true;
      }
    }
  }

  int removed = 0, x1 = 2, x2 = 2;
  int sz = primes.size();
  vector<int> mul_cnt_suff_max_at(sz);
  for (int i = sz - 1; i >= 0; i--) {
    if (mul_cnt[primes[i]] > removed) {
      removed = mul_cnt[primes[i]];
      x1 = x2 = primes[i];
    }
    int j;
    for (j = i + 1; j < sz; j++) {
      if (1ll * primes[i] * primes[j] > mx_a) break;
      int cur = mul_cnt[primes[i]] + mul_cnt[primes[j]] - mul_cnt[primes[i] * primes[j]];
      if (cur > removed) {
        removed = cur;
        x1 = primes[i];
        x2 = primes[j];
      }
    }
    if (j < sz) {
      j = mul_cnt_suff_max_at[j];
      int cur = mul_cnt[primes[i]] + mul_cnt[primes[j]];
      if (cur > removed) {
        removed = cur;
        x1 = primes[i];
        x2 = primes[j];
      }
    }

    if (i == sz - 1 or mul_cnt[primes[i]] > mul_cnt[primes[mul_cnt_suff_max_at[i + 1]]]) {
      mul_cnt_suff_max_at[i] = i;
    }
    else {
      mul_cnt_suff_max_at[i] = mul_cnt_suff_max_at[i + 1];
    }
  }

  cout << (n - removed) << "\n";
  cout << x1 << " " << x2 << "\n";

  return 0;
}