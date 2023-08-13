#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  vector<int> left_small(n), left_big(n);
  for (int i = 0; i < n; i++) {
    left_small[i] = left_big[i] = i - 1;
    while (left_small[i] >= 0 and p[left_small[i]] > p[i]) left_small[i] = left_small[left_small[i]];
    while (left_big[i] >= 0 and p[left_big[i]] < p[i]) left_big[i] = left_big[left_big[i]];
  }

  vector<int> right_small(n), right_big(n);
  for (int i = n - 1; i >= 0; i--) {
    right_small[i] = right_big[i] = i + 1;
    while (right_small[i] < n and p[right_small[i]] > p[i]) right_small[i] = right_small[right_small[i]];
    while (right_big[i] < n and p[right_big[i]] < p[i]) right_big[i] = right_big[right_big[i]];
  }

  long long ans = 0;
  for (int mn_pos = 0; mn_pos < n; mn_pos++) {
    if (right_small[mn_pos] - mn_pos <= mn_pos - left_small[mn_pos]) {
      int L = n;
      for (int mx_pos = mn_pos + 1; mx_pos < right_small[mn_pos]; mx_pos++) {
        L = min(L, left_big[mx_pos]);
        assert(L < mn_pos);
        ans += mn_pos - max(left_small[mn_pos], L);
      }
    }
    else {
      int R = -1;
      for (int left_end = mn_pos; left_end > left_small[mn_pos]; left_end--) {
        R = max(R, right_big[left_end]);
        assert(R > mn_pos);
        ans += max(0, right_small[mn_pos] - R);
      }
    }
  }

  cout << ans << "\n";

  return 0;
}