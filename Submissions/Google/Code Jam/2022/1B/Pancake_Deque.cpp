#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  deque<int> dq;
  for (int i = 0; i < n; i++) {
    int d;
    cin >> d;
    dq.push_back(d);
  }

  int ans = 0;
  int mx = 0;

  while (!dq.empty()) {
    if (dq.front() < mx) dq.pop_front();
    else if (dq.back() < mx) dq.pop_back();
    else if (dq.front() <= dq.back()) mx = dq.front(), dq.pop_front(), ans++;
    else mx = dq.back(), dq.pop_back(), ans++;
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}