#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, d;
  cin >> n >> m >> d;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll ans = 0;
  ll positive_sum = 0;

  multiset<int> ms;

  for (int i = 0; i < n; i++) {
    if (a[i] >= 0) {
      positive_sum += a[i];
      ans = max(ans, positive_sum - 1ll * (i + 1) * d);

      ms.insert(a[i]);
      if (ms.size() >= m) {
        positive_sum -= *ms.begin();
        ms.erase(ms.begin());
      }
    }
  }

  cout << ans << "\n";
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