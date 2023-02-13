#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  multiset<int> ms;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    ms.insert(a);
  }

  long long ans = 0;
  ans += *ms.rbegin();
  ans += *next(ms.rbegin());
  ans -= *ms.begin();
  ans -= *next(ms.begin());

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