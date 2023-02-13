#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> k(n), h(n);
  for (int &i : k) cin >> i;
  for (int &i : h) cin >> i;

  map<int, int> freq;
  for (int i : k) freq[i]--;
  for (int i = 0; i < n; i++) {
    freq[k[i] - h[i] + 1]++;
  }

  int c = 0;
  long long ans = 0;
  int l;

  for (auto [v, f] : freq) {
    if (c == 0) l = v;
    c += f;
    if (c == 0) {
      int r = v;
      int len = r - l + 1;
      ans += (long long)len * (len + 1) / 2;
    }
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