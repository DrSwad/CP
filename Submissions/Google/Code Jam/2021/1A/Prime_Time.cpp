#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const long double eps = 1e-6;

int m;
vector<pair<int, ll>> p;
ll totSum;
ll ans;

void solve(int at, ll currProd = 1, ll currSum = 0) {
  if (at == m) {
    if (currProd == totSum - currSum) {
      ans = max(ans, currProd);
    }
    return;
  }

  solve(at + 1, currProd, currSum);
  for (int take = 1; take <= p[at].second; take++) {
    currSum += p[at].first;
    ll remSum = totSum - currSum;
    if ((long double)remSum / currProd + eps < p[at].first) {
      break;
    }
    currProd *= p[at].first;
    solve(at + 1, currProd, currSum);
  }
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    scanf("%d", &m);

    p.clear();
    totSum = 0;
    for (int i = 0; i < m; i++) {
      int prime;
      ll n;
      scanf("%d %lld", &prime, &n);
      p.emplace_back(prime, n);
      totSum += n * prime;
    }

    ans = 0;
    solve(0);
    printf("Case #%d: %lld\n", cs, ans);
  }

  return 0;
}