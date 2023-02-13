#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int max_xor = 2 * n + 10;
  vector<int> freq(max_xor, 0);
  freq[0]++;
  for (int i = 0, pref = 0; i < n; i++) {
    pref ^= a[i];
    freq[pref]++;
  }

  long long ans = n * 1ll * (n + 1) / 2;
  for (int i = 1; i * i < max_xor; i++) {
    int sq = i * i;
    for (int j = 0; j < max_xor; j++) {
      int k = j ^ sq;
      if (k < max_xor and k < j) {
        ans -= 1ll * freq[j] * freq[k];
      }
    }
  }
  for (int i = 0; i < max_xor; i++) {
    ans -= 1ll * freq[i] * (freq[i] - 1) / 2;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}