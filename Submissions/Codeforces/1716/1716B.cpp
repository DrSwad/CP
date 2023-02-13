#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  iota(p.begin(), p.end(), 1);

  cout << n << "\n";
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) cout << " ";
      cout << p[j];
    }
    cout << "\n";

    if (i < n - 1) {
      swap(p[i], p[i + 1]);
    }
  }
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