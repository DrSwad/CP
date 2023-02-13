#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s, t;
  cin >> s >> t;

  queue<int> q[3];
  for (int i = 0; i < n; i++) {
    q[s[i] - 'a'].push(i);
  }

  for (int i = 0; i < n; i++) {
    int ct = t[i] - 'a';
    int cs, cp = n;
    for (int j = 0; j < 3; j++) {
      if (!q[j].empty() and q[j].front() < cp) cs = j, cp = q[j].front();
    }

    if (ct == cs) {
      q[cs].pop();
    }
    else {
      int cu = (ct + 1) % 3;
      if (ct != cs + 1 or q[ct].empty() or !q[cu].empty() and q[cu].front() < q[ct].front()) {
        cout << "NO\n";
        return;
      }
      q[ct].pop();
    }
  }

  cout << "YES\n";
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