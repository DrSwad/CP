#include <bits/stdc++.h>
using namespace std;

vector<int> ans;

bool go(int sum, int prod) {
  if (prod == 1) {
    while (sum--) ans.push_back(1);
    return true;
  }

  if (sum == 0) return false;

  for (int i = 2; i <= min(sum, prod); i++) {
    if (prod % i == 0) {
      ans.push_back(i);
      if (go(sum - i, prod / i)) return true;
      ans.pop_back();
    }
  }

  return false;
}

void test_case() {
  int p;
  cin >> p;

  debug(p);

  ans.clear();
  if (go(41, p)) {
    cout << " " << ans.size();
    for (int i : ans) cout << " " << i;
    cout << "\n";
  }
  else cout << " -1\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ":";
    test_case();
  }

  return 0;
}