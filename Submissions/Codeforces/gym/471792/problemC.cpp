#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  string s;
  cin >> s;

  if (count(s.begin(), s.end(), '0') != count(s.begin(), s.end(), '1')) {
    cout << "-1\n";
    return;
  }

  vector<int> ans;

  int l = 0, r = n - 1;
  while (l < r) {
    if (s[l] != s[r]) l++, r--;
    else {
      if (s[l] == '0') {
        ans.push_back(r + 1);
        s.insert(s.begin() + r + 1, '1');
        s.insert(s.begin() + r + 1, '0');
        l++, r++;
      }
      else {
        ans.push_back(l);
        s.insert(s.begin() + l, '1');
        s.insert(s.begin() + l, '0');
        l += 2, r += 2;
        l--, r--;
      }
    }
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  if (!ans.empty()) cout << "\n";
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