#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  vector<long long> p(n + 1);
  p[0] = 0;
  for (int i = 1; i <= n; i++) {
    p[i] = p[i - 1] + b[i - 1];
  }

  int ans = -1;

  vector<int> mn(k + 1, -1);
  mn[0] = 0;

  for (int r = n - 1; r >= 0; r--) {
    for (int l = 0; l <= r; l++) {
      long long B = p[r + 1] - p[l];
      if (B > k) continue;
      int need = k - B;
      if (mn[need] == -1) continue;
      int curr = (r - l + 1) + mn[need];
      ans = ans == -1 ? curr : min(ans, curr);
    }

    for (int rr = r; rr < n; rr++) {
      long long B = p[rr + 1] - p[r];
      if (B > k) continue;
      int curr = rr - r + 1;
      if (mn[B] == -1 or mn[B] > curr) {
        mn[B] = curr;
      }
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}