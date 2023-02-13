#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> f(n, 0);
  while (m--) {
    int a, b, c;
    cin >> a >> b >> c;
    f[b - 1]++;
  }

  int root = -1;
  for (int i = 0; i < n; i++) {
    if (f[i] == 0) root = i + 1;
  }

  assert(~root);

  for (int i = 1; i <= n; i++) {
    if (i != root) {
      cout << i << " " << root << "\n";
    }
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}