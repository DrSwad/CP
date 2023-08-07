#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  set<int> mask_vis;
  long long ans;
  queue<int> q;

  q.push(0);
  mask_vis.insert(0);
  ans = 0;

  while (!q.empty()) {
    int mask = q.front();
    q.pop();

    for (int i = 0; i < n - k + 1; i++) {
      int nmask = mask;
      for (int j = i; j <= i + k - 1; j++) {
        nmask ^= 1 << j;
      }
      if (mask_vis.find(nmask) == mask_vis.end()) {
        mask_vis.insert(nmask);
        q.push(nmask);
        long long sum = 0;
        for (int j = 0; j < n; j++) {
          if (nmask >> j & 1) {
            sum += a[j];
          }
        }
        ans = max(ans, sum);
      }
    }
  }

  cout << ans << "\n";

  return 0;
}