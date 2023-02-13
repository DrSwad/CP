#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 998244353;

int n;
vector<pair<char, int>> a;

int existsFreq(int index) {
  vector<int> remaining_freq(n, 0);
  remaining_freq[0] = 1;

  for (int i = 0; i < n; i++) {
    if (i == index) continue;

    if (a[i].first == '-') {
      if (i < index) (remaining_freq[0] *= 2) %= MOD;
      for (int j = 0; j < n - 1; j++) {
        (remaining_freq[j] += remaining_freq[j + 1]) %= MOD;
      }
    } else {
      if (a[i].second > a[index].second or
          (a[i].second == a[index].second and i > index)) {
        for (int j = 0; j < n; j++) {
          (remaining_freq[j] *= 2) %= MOD;
        }
      } else {
        for (int j = n - 1; j; j--) {
          (remaining_freq[j] += remaining_freq[j - 1]) %= MOD;
        }
      }
    }
  }

  ll ret = 0;
  for (int freq : remaining_freq) ret += freq;
  return ret % MOD;
}

int main() {
  cin >> n;
  a.resize(n);
  for (auto& [op, x] : a) {
    scanf(" %c", &op);
    if (op == '+') scanf("%d", &x);
  }

  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (a[i].first == '+') {
      (ans += (ll)existsFreq(i) * a[i].second % MOD) %= MOD;
    }
  }

  cout << ans << endl;

  return 0;
}