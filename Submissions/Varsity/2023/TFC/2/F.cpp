#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k, x;
  ll m;
  cin >> n >> k >> m >> x;

  if (k == 1) {
    if (m == n) cout << "yes\n";
    else cout << "no\n";
  }
  else {
    vector<int> d;
    while (m) {
      int r = m % k;
      d.push_back(r);
      m /= k;
    }

    if (d[0] > 1 or * max_element(d.begin(), d.end()) > 2) {
      cout << "no\n";
      return;
    }

    int used = accumulate(d.begin(), d.end(), 0);
    if (used > n) {
      cout << "no\n";
      return;
    }

    for (int i = 2; i < d.size() and used < n; i++) {
      int j = i;
      while (j >= 2 and d[j] and d[j - 1] + k <= 2 and used < n) {
        d[j]--;
        d[j - 1] += k;
        used += k - 1;
        j--;
      }
    }

    if (used == n) cout << "yes\n";
    else cout << "no\n";
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