#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, l;
  cin >> n >> l;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  a.insert(a.begin(), 0);
  a.push_back(l + 1);
  b.insert(b.begin(), 0);
  b.push_back(l + 1);
  n = a.size();

  map<int, int> fa, fb;
  for (int i = 0; i < n; i++) {
    fa[a[i] - i]++;
    fb[b[i] - i]++;
  }

  for (auto [f, c] : fb) {
    if (fa[f] == 0) {
      cout << "-1\n";
      return 0;
    }
  }

  long long ans = 0, carry = 0;
  for (auto [f, ca] : fa) {
    int cb = fb[f];
    if (cb > 0) {
      ans += abs(carry);
    }
    else if (carry < 0) {
      ans += min(abs(carry), (long long)ca);
    }
    carry += ca;
    carry -= cb;
  }

  cout << ans << "\n";

  return 0;
}