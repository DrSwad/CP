#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  map<int, int> freq;
  for (int &i : a) {
    cin >> i;
    freq[i]++;
  }

  a.clear();
  for (auto [v, f] : freq) {
    a.push_back(f);
  }
  n = a.size();

  const int p = 18;
  int ans = INT_MAX;

  for (int p1 = 0; p1 <= p; p1++) {
    int v1 = 1 << p1;
    for (int p2 = 0; p2 <= p; p2++) {
      int v2 = 1 << p2;

      int s1 = 0, s2 = 0, s3 = 0;
      int i = 0;
      while (i < n and s1 + a[i] <= v1) s1 += a[i], i++;
      while (i < n and s2 + a[i] <= v2) s2 += a[i], i++;
      while (i < n) s3 += a[i], i++;

      int msb = s3 == 0 ? -1 : 31 - __builtin_clz(s3);
      int v3 = s3 == 0 ? 1 : 1 << msb;
      if (s3 > v3) v3 *= 2;

      int curr = (v1 - s1) + (v2 - s2) + (v3 - s3);
      ans = min(ans, curr);
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