#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;

int add(int a, int b) {
  int c = (a + b);
  return c >= MOD ? c - MOD : c;
}

int mul(int a, int b) {
  return 1ll * a * b % MOD;
}

int rem(vector<int> v, int b) {
  int ret = 0;
  for (int d : v) {
    ret = add(mul(ret, b), d);
  }
  return ret;
}

void test_case() {
  int n, b;
  cin >> n >> b;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n < b) {
    vector<int> na(b, 0);
    for (int i = n - 1, j = b - 1; i >= 0; i--, j--) {
      na[j] = a[i];
    }
    swap(a, na);
    n = b;
  }

  set<int> available_digits;
  for (int d = 0; d < b; d++) {
    available_digits.insert(d);
  }

  vector<int> c(n);
  int i;
  for (i = 0; i < n; i++) {
    int d = a[i];
    if ((i == 0 and d == 0) or !available_digits.count(d)) break;
    c[i] = d;
    available_digits.erase(d);
  }

  if (i == n) {
    cout << "0\n";
    return;
  }

  if (available_digits.upper_bound(a[i]) == available_digits.end()) {
    i--;
    while (i >= 0) {
      available_digits.insert(c[i]);
      if (available_digits.upper_bound(a[i]) != available_digits.end()) break;
      i--;
    }
  }

  if (i == -1) {
    n++;
    a.insert(a.begin(), 0);
    c.insert(c.begin(), 1);
    available_digits.erase(1);
    c[1] = 0;
    i = 2;
  }
  else {
    c[i] = *available_digits.upper_bound(a[i]);
    available_digits.erase(c[i]);
    i++;
  }

  while (i < n) {
    assert(!available_digits.empty());
    c[i] = *available_digits.begin();
    i++;
    available_digits.erase(available_digits.begin());
  }

  int ra = rem(a, b);
  int rc = rem(c, b);
  int x = (rc - ra + MOD) % MOD;
  cout << x << "\n";
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