#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<ll> a(n);
  for (ll &i : a) cin >> i;

  int neg = 0, zero = 0, pos = 0;
  vector<ll> b;
  for (ll i : a) {
    if (i < 0) {
      neg++;
      if (neg >= 3) {
        cout << "NO\n";
        return;
      }
      b.push_back(i);
    }
    else if (i > 0) {
      pos++;
      if (pos >= 3) {
        cout << "NO\n";
        return;
      }
      b.push_back(i);
    }
    else {
      zero++;
      if (zero <= 3) {
        b.push_back(i);
      }
    }
  }

  swap(a, b);
  n = a.size();
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      for (int k = j + 1; k < n; k++) {
        if (find(a.begin(), a.end(), a[i] + a[j] + a[k]) == a.end()) {
          cout << "NO\n";
          return;
        }
      }
    }
  }

  cout << "YES\n";
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