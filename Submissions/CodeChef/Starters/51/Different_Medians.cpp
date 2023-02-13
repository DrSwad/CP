#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  deque<int> rem(n);
  iota(rem.begin(), rem.end(), 1);

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    if (i & 1) cout << rem.front(), rem.pop_front();
    else cout << rem.back(), rem.pop_back();
  }
  cout << "\n";
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