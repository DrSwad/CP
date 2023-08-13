#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<int> z_function(int n, const T &s) {
  vector<int> z(n, n);
  int l = 0, r = 0;
  for (int i = 1; i < n; i++) {
    z[i] = (i > r ? 0 : min(r - i + 1, z[i - l]));
    while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i;
      r = i + z[i] - 1;
    }
  }
  return z;
}

template<typename T>
vector<int> z_function(const T &s) {
  return z_function((int) s.size(), s);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  if (m == 1) {
    cout << n << "\n";
    return 0;
  }

  vector<int> a(n), b(m);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  for (int i = n - 1; i >= 1; i--) a[i] -= a[i - 1];
  for (int i = m - 1; i >= 1; i--) b[i] -= b[i - 1];
  a.erase(a.begin());
  b.erase(b.begin());
  n--, m--;

  vector<int> c;
  for (int i : b) c.push_back(i);
  for (int i : a) c.push_back(i);

  vector<int> z = z_function(c);
  int ans = 0;
  for (int i = m; i < c.size(); i++) {
    ans += z[i] >= m;
  }

  cout << ans << "\n";

  return 0;
}