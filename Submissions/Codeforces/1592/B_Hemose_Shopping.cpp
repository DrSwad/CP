#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  bool ans;

  if (n == x) ans = is_sorted(a.begin(), a.end());
  else {
    vector<int> aa = a;
    sort(aa.begin(), aa.end());
    int st = n - x;
    int en = x - 1;

    if (st > en) ans = true;
    else {
      ans = true;
      for (int i = st; i <= en; i++) {
        if (aa[i] != a[i]) {
          ans = false;
          break;
        }
      }
    }
  }

  cout << (ans ? "YES" : "NO") << "\n";
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