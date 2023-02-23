#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<tuple<int, int, int>> a(n);
  for (int i = 0; i < n; i++) {
    auto & [r, s, ii] = a[i];
    cin >> r >> s;
    ii = i + 1;
  }

  sort(a.begin(), a.end());

  vector<int> ans{get<2>(a.back())};
  tuple<int, int, int> lst = a.back();

  for (int i = n - 2; i >= 0; i--) {
    if (get<1>(a[i]) > get<1>(lst) or
        (get<1>(a[i]) == get<1>(lst) and get<0>(a[i]) == get<0>(lst))
        )  {
      ans.push_back(get<2>(a[i]));
      lst = a[i];
    }
  }

  sort(ans.begin(), ans.end());
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}