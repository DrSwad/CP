#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  string s;
  cin >> s;

  vector<int> cnt(2, 0);
  for (int i = 0; i < k - 1; i++) {
    cnt[s[i] == 'B']++;
  }

  int minW = k;
  for (int i = k - 1; i < n; i++) {
    cnt[s[i] == 'B']++;
    if (i >= k) cnt[s[i - k] == 'B']--;
    minW = min(minW, cnt[0]);
  }

  cout << minW << "\n";
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