#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string a, b;
  cin >> a >> b;

  vector<int> pref(n + 1);
  pref[0] = 0;
  for (int i = 0; i < n; i++) {
    pref[i + 1] = pref[i] ^ (a[i] - '0');
  }

  vector<int> ans;
  queue<int> q;

  for (int i = n - 1; i >= 0; i--) {
    if (a[i] != b[i]) {
      if (pref[i] != 1) q.push(i);
      else {
        ans.push_back(i);
        while (!q.empty()) {
          ans.push_back(q.front());
          q.pop();
        }
      }
    }
  }

  if (!q.empty()) {
    int at = find(a.begin(), a.end(), '1') - a.begin();
    if (at == n) {
      cout << "-1\n";
      return;
    }
    else {
      ans.push_back(at + 1);
      while (!q.empty()) {
        int i = q.front();
        q.pop();
        if (i <= at) {
          cout << "-1\n";
          return;
        }
        assert(i != at + 1);
        ans.push_back(i);
      }
      ans.push_back(at + 1);
    }
  }

  if (ans.size() > n) cout << "-1\n";
  else {
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
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