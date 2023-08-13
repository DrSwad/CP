#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n), b(n);
  for (int &i : a) cin >> i;
  for (int &i : b) cin >> i;

  ll ans = 0;

  function<void(int, int, int, ll)> f =
    [&](int at, int len, int start, ll sum) {
      if (at == n) {
        if (start == -1 and len == k) {
          ans = max(ans, sum);
        }
        return;
      }

      if (start != -1) {
        len++;
        f(at + 1, len, start, sum);
        f(at + 1, len, -1, sum + abs(b[start] - a[at]) + abs(b[at] - a[start]));
      }
      else {
        f(at + 1, len, start, sum);
        f(at, len, at, sum);
      }
    };

  f(0, 0, -1, 0);

  cout << ans << "\n";
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