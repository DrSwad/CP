#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ll s;
  cin >> s;
  s *= 2;

  int n;
  cin >> n;

  vector<pair<ll, ll>> p(n);
  for (auto & [x, y] : p) {
    cin >> x >> y;
  }

  auto area = [&](vector<int> ids) {
    ll ret = 0;
    int n = ids.size();
    for (int i = 0; i < n; i++) {
      ret += (p[ids[i]].first * p[ids[(i + 1) % n]].second);
    }
    for (int i = 0; i < n; i++) {
      ret -= (p[ids[i]].second * p[ids[(i + 1) % n]].first);
    }
    return abs(ret);
  };

  ll ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      for (int k = 0; k < n; k++) {
        for (int l = 0; l < n; l++) {
          if (i != j and i != k and i != l and j != k and j != l and k != l) {
            bool is_simple = false;
            is_simple = is_simple or area({i, j, k, l}) == area({i, k, j}) + area({i, k, l});
            is_simple = is_simple or area({i, j, k, l}) == area({j, l, k}) + area({j, l, i});
            if (is_simple and area({i, j, k, l}) >= s) {
              // debug(i, j, k, l);
              ans++;
            }
          }
        }
      }
    }
  }

  cout << ans / 8 << endl;

  return 0;
}