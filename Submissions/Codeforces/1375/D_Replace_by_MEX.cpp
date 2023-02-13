#include <bits/stdc++.h>
using namespace std;

int mex(const vector<int> &a) {
  int n = a.size();
  vector<int> f(n + 1, 0);
  for (int i : a) f[i]++;
  for (int i = 0; i <= n; i++) {
    if (!f[i]) return i;
  }
  assert(false);
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> ans;
  while (!is_sorted(a.begin(), a.end())) {
    int m = mex(a);

    bool flag = true;
    for (int i = n - 1; i >= m; i--) {
      if (a[i] != i + 1) {
        flag = false;
        break;
      }
    }

    int p = flag ? m - 1 : m;
    a[p] = m;
    ans.push_back(p + 1);
  }

  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
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