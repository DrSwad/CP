#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, b, k1, k2;
  cin >> n >> b >> k1 >> k2;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  ll sum = 0;
  for (int i : a) sum += i;

  ll ans = sum;

  auto add = [&](int i) {
    return max(0, a[i] - b) - (a[i] + 1) / 2;
  };

  for (int both = 0; both <= min(n, min(k1, k2)); both++) {
    ll cur = sum;
    for (int i = n - 1; i >= n - both; i--) {
      cur -= a[i];
      cur += max(0, (a[i] + 1) / 2 - b);
    }

    int nk1 = k1 - both, nk2 = k2 - both;
    assert(nk1 >= 0 and nk2 >= 0);
    int r = n - 1 - both, l = max(0, r - nk1 - nk2 + 1);
    assert(0 <= l and r <= n - 1 and r - l + 1 <= nk1 + nk2);

    if (l <= r) {
      for (int i = l; i <= r; i++) {
        cur -= a[i];
        cur += (a[i] + 1) / 2;
      }

      int min_k2 = max(0, (r - l + 1) - nk1);
      int max_k2 = min(r - l + 1, nk2);
      assert(0 <= min_k2 and min_k2 <= max_k2 and max_k2 <= r - l + 1);

      if (max_k2 > 0) {
        int i1, i2;
        for (i1 = r; i1 >= l; i1--) if (a[i1] <= b) break;
        for (i2 = l; i2 <= r; i2++) if (a[i2] > b) break;

        int at;
        if (i1 < l) at = i2;
        else if (i2 > r) at = i1;
        else if (add(i1) <= add(i2)) at = i1;
        else at = i2;
        assert(l <= at and at <= r);

        if (add(at) < 0 or min_k2 > 0) {
          int L = at, R = at;
          cur += add(at);

          while (R - L + 1 < max_k2) {
            int i;
            if (R == r) i = L - 1;
            else if (L == l) i = R + 1;
            else if (add(L - 1) <= add(R + 1)) i = L - 1;
            else i = R + 1;

            if (add(i) >= 0 and R - L + 1 >= min_k2) break;
            cur += add(i);
            L = min(L, i), R = max(R, i);
          }
        }
      }
    }

    ans = min(ans, cur);
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
