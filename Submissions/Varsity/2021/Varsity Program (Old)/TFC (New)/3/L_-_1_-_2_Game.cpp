#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  vector<int> rem_freq(3, 0);
  for (int &i : a) cin >> i, rem_freq[i % 3]++;

  int ans = 0;

  for (int i = 0; i < n; i++) {
    rem_freq[a[i] % 3]--;
    rem_freq[(a[i] + 2) % 3]++;

    ans += rem_freq[1] > 0 or rem_freq[2] > 1 or rem_freq[2] == 0;

    rem_freq[a[i] % 3]++;
    rem_freq[(a[i] + 2) % 3]--;
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