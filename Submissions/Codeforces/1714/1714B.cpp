#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  vector<int> f(n, 0);
  map<int, int> f2;
  for (int &i : a) {
    cin >> i, i--;
    f[i]++;
  }

  for (int i = 0; i < n; i++) {
    if (f[i]) f2[f[i]]++;
  }

  int ans;
  for (ans = 0; ans < n; ans++) {
    if (f2.rbegin()->first == 1) break;

    f2[f[a[ans]]]--;
    if (f2[f[a[ans]]] == 0) {
      f2.erase(f[a[ans]]);
    }

    f[a[ans]]--;
    f2[f[a[ans]]]++;
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