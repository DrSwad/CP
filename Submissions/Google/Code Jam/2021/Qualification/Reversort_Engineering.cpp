#include <bits/stdc++.h>
using namespace std;

vector<int> solve(vector<int> a, long long c) {
  int n = a.size();
  if (n == 1) return a;

  int take = min(c, (long long)n - 1);
  vector<int> rest =
      solve(vector<int>(a.begin() + 1, a.end()), c - take);

  vector<int> ret;
  copy(rest.begin(), rest.begin() + take, back_inserter(ret));
  reverse(ret.begin(), ret.end());
  ret.push_back(a[0]);
  copy(rest.begin() + take, rest.end(), back_inserter(ret));

  return ret;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    printf("Case #%d:", cs);

    int n;
    long long c;
    scanf("%d %lld", &n, &c);

    if (c < n - 1 or c > 1ll * n * (n + 1) / 2 - 1) {
      puts(" IMPOSSIBLE");
    } else {
      vector<int> a(n);
      iota(a.begin(), a.end(), 1);
      vector<int> ans = solve(a, c - (n - 1));

      for (int i = 0; i < n; i++) { printf(" %d", ans[i]); }
      puts("");
    }
  }

  return 0;
}