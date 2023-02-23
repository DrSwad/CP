#include <bits/stdc++.h>
using namespace std;

const int WALK_DURATION = 120;
const int DAY_DURATION = 1440;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int cnt = 0;
  for (int i = 0; i < n - 1; i++) {
    cnt += (a[i + 1] - a[i]) / WALK_DURATION;
  }
  cnt += a[0] / WALK_DURATION;
  cnt += (DAY_DURATION - a[n - 1]) / WALK_DURATION;

  if (cnt >= 2) cout << "YES\n";
  else cout << "NO\n";
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
