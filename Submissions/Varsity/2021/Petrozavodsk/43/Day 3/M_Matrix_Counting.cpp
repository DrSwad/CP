#include <bits/stdc++.h>
using namespace std;

void brute() {
  for (int n = 1; n <= 8; n++) {
    DB();
    debug(n);

    vector<int> p(n);
    iota(p.begin(), p.end(), 0);
    vector<int> ans(n, 0);

    do {
      int mx = 0;
      for (int i = 0; i < n; i++) {
        set<int> st;
        for (int j = i; j < n; j++) {
          if (j - i == n - 1) continue;
          st.insert(p[j]);
          if (*st.rbegin() - *st.begin() == j - i) {
            mx = max(mx, j - i);
          }
        }
      }
      ans[mx]++;
    } while (next_permutation(p.begin(), p.end()));

    debug(ans);
  }
}

void test_case() {}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  brute();

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}