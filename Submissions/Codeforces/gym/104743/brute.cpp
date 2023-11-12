#include <bits/stdc++.h>
using namespace std;

const int M = 1000;

void test_case() {
  int n, q;
  cin >> n >> q;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  while (q--) {
    int l, r;
    cin >> l >> r;

    int m;
    for (m = 1; m <= M; m++) {
      bool okay = true;
      for (int i = l - 1; i < r; i++) {
        if (a[i] % m != b[i]) {
          okay = false;
          break;
        }
      }
      if (okay) break;
    }

    if (m <= M) cout << m << "\n";
    else cout << "-1\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}