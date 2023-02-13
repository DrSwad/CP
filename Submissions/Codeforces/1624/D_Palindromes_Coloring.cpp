#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<int> freq(26, 0);
  for (char c : s) {
    int ch = c - 'a';
    freq[ch]++;
  }

  int pairs = 0;
  for (int ch = 0; ch < 26; ch++) {
    pairs += freq[ch] / 2;
  }

  int ans = 0;
  for (int i = 0; i <= pairs; i++) {
    int j = n - 2 * i;
    ans = max(ans, i / k * 2 + (k - i % k <= j));
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