#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int x;
  cin >> x;

  vector<int> ans;
  ans.push_back(1);

  while (ans.back() * 2 < x) {
    ans.push_back(ans.back() * 2);
  }
  x -= ans.back();

  while (x) {
    int msb = 31 - __builtin_clz(x);
    ans.push_back(ans.back() + (1 << msb));
    x -= 1 << msb;
  }

  reverse(ans.begin(), ans.end());
  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
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