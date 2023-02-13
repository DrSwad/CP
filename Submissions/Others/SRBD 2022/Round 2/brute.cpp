#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  scanf("%d", &n);

  vector<vector<pair<int, bool>>> e(n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      int r;
      char c;
      scanf(" (%d, %c)", &r, &c);
      e[i].push_back({r, c == 'T'});
    }
  }

  function<ll(vector<int>&)> solve = [&](vector<int> &perm) {
    ll ans = 0;
    int a = perm[0];
    for (int i = 1; i < n; i++) {
      int b = perm[i];
      ans += e[a][b].first;
      a = e[a][b].second ? a : b;
    }
    return ans;
  };

  ll ans = 0;
  vector<int> p(n);
  iota(p.begin(), p.end(), 0);

  do {
    ans = max(ans, solve(p));
  } while (next_permutation(p.begin(), p.end()));

  printf("%lld\n", ans);
}

int main() {
  int t;
  scanf("%d", &t);

  for (int cs = 1; cs <= t; cs++) {
    printf("Case %d: ", cs);
    test_case();
  }

  return 0;
}