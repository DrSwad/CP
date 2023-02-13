#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, H, M;
  cin >> n >> H >> M;

  vector<int> v;
  for (int i = 0; i < n; i++) {
    int h, m;
    cin >> h >> m;
    v.push_back(h * 60 + m);
  }

  sort(v.begin(), v.end());
  v.push_back(v[0] + 24 * 60);

  int curr = H * 60 + M;
  int ans = *lower_bound(v.begin(), v.end(), curr) - curr;
  cout << (ans / 60) << " " << (ans % 60) << "\n";
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