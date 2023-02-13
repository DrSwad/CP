#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  map<int, int> f, ff;
  while (n--) {
    int a;
    cin >> a;
    ff[f[a]]--;
    f[a]++;
    ff[f[a]]++;
  }

  if (ff.rbegin()->second == 1) cout << "YES\n";
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