#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, m, d;
  cin >> n >> m >> d;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll ans = 0;
  multiset<int> ms; // [0...i-1] porjonto at most (m-1)ta largest positives
  ll ms_sum = 0;

  for (int i = 0; i < n; i++) {
    if (a[i] >= 0) {
      ans = max(ans, ms_sum + a[i] - 1ll * (i + 1) * d);

      ms_sum += a[i];
      ms.insert(a[i]);
      if (ms.size() == m) {
        ms_sum -= *ms.begin();
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