#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  deque<int> ans;
  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;

    if (ans.empty() or a < ans.front()) ans.push_front(a);
    else ans.push_back(a);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << ans.front();
    ans.pop_front();
  }
  cout << "\n";
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