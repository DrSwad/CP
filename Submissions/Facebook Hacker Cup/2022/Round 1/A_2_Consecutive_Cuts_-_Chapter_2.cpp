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

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  string s;
  for (int i : b) s += '0' + i;
  for (int i : a) s += '0' + i;
  for (int i : a) s += '0' + i;

  vector<int> z = z_function(s);

  if (k == 0) return void(cout << (z[n] >= n ? "YES\n" : "NO\n"));
  if (k == 1) {
    for (int i = n + 1; i < 2 * n; i++) {
      if (z[i] >= n) return void(cout << "YES\n");
    }
    return void(cout << "NO\n");
  }
  if (n == 2) {
    return void(cout << (z[n + (k % 2)] >= n ? "YES\n" : "NO\n"));
  }
  if (n >= 3) {
    for (int i = n; i < 2 * n; i++) {
      if (z[i] >= n) return void(cout << "YES\n");
    }
    return void(cout << "NO\n");
  }
  assert(false);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}