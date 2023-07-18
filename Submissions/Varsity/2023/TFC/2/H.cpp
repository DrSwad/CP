#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int m, n;
  cin >> m >> n;

  vector<int> s(m);
  for (int &i : s) cin >> i;
  sort(s.begin(), s.end());

  vector<char> d(n, 0);
  vector<int> from(n, -1);
  queue<int> q;

  for (int i : s) {
    if (i) {
      int rem = i % n;
      if (d[rem] == 0) {
        q.push(i);
        d[rem] = '0' + i;
      }
    }
  }

  while (!q.empty()) {
    int at_rem = q.front();
    q.pop();

    for (int i : s) {
      int new_rem = (at_rem * 10 + i) % n;

      if (d[new_rem] == 0) {
        q.push(new_rem);
        d[new_rem] = '0' + i;
        from[new_rem] = at_rem;
      }
    }
  }

  if (d[0] == 0) cout << "-1\n";
  else {
    stack<char> ans;
    int at = 0;
    while (at != -1) {
      ans.push(d[at]);
      at = from[at];
    }
    while (!ans.empty()) {
      cout << ans.top();
      ans.pop();
    }
    cout << "\n";
  }
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