#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> dist_freq(n + m, 0);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      int dist = max(i, (n - 1) - i) + max(j, (m - 1) - j);
      dist_freq[dist]++;
    }
  }

  for (int got = 0, dist = 0; got < n * m; got++) {
    while (dist_freq[dist] == 0) {
      dist++;
      assert(dist < n + m);
    }
    if (got) cout << " ";
    cout << dist;
    dist_freq[dist]--;
  }
  cout << "\n";
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