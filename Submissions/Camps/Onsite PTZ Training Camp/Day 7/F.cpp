#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int rows, cols;
  cin >> rows >> cols;

  vector<int> a(rows - 1), b(cols), c(rows), d(cols - 1);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;
  for (int &i : c) cin >> i;
  for (int &i : d) cin >> i;

  long long ans = 0;
  for (int row = 0; row < rows - 1; row++) ans += b[0] + a[row];
  for (int col = 0; col < cols - 1; col++) ans += c[0] + d[col];

  long long sum = 0;
  vector<int> diffs;
  for (int col = 1; col < cols; col++) {
    sum += b[col];
    diffs.push_back(d[col - 1] - b[col]);
  }
  sort(diffs.begin(), diffs.end());

  vector<long long> pref(cols);
  pref[0] = 0;
  for (int i = 1; i < cols; i++) {
    pref[i] = pref[i - 1] + diffs[i - 1];
  }

  for (int row = 1; row < rows; row++) {
    ans += 1ll * a[row - 1] * (cols - 1) + sum;
    int diff = c[row] - a[row - 1];
    int cnt = lower_bound(diffs.begin(), diffs.end(), -diff) - diffs.begin();
    ans += pref[cnt];
    ans += 1ll * diff * cnt;
  }

  cout << ans << "\n";

  return 0;
}