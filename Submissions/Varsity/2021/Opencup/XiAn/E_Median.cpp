#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void answer(bool ans) {
  cout << (ans ? "YES\n" : "NO\n");
}

void test_case() {
  int n;
  cin >> n;

  vector<pair<int, int>> v(n);
  vector<vector<int>> ids(2);

  for (int i = 0; i < n; i++) {
    auto & [a, b] = v[i];
    cin >> a >> b;
    b -= a;
    if (a or b) ids[a > 0].push_back(i);
  }

  if (ids[1].size() == 0) return answer(false);
  if (ids[0].size() == 0) return answer(true);

  ll way1 = 0;
  for (int id : ids[1]) {
    way1 += v[id].second;
  }

  ll way2 = 0;
  for (int id0 = (int)ids[0].size() - 1, id1 = (int)ids[1].size() - 1, rem0 = v[ids[0][id0]].second, rem1 = v[ids[1][id1]].first; id0 >= 0 and id1 >= 0; ) {
    if (rem0 == 0) {
      id0--;
      if (id0 >= 0) rem0 = v[ids[0][id0]].second;
      continue;
    }
    if (rem1 == 0 or ids[0][id0] < ids[1][id1]) {
      id1--;
      if (id1 >= 0) rem1 = v[ids[1][id1]].first;
      continue;
    }
    int take = min(rem0, rem1);
    way2 += take;
    rem0 -= take;
    rem1 -= take;
  }

  // debug(way1, way2);

  vector<ll> left(n), right(n);
  {
    ll curr = 0;
    for (int i = 0; i < n; i++) {
      auto [a, b] = v[i];
      if (a == 0) curr += b;
      else left[i] = curr;
    }
  }
  {
    ll curr = 0;
    for (int i = n - 1; i >= 0; i--) {
      auto [a, b] = v[i];
      if (a == 0) curr += b;
      else right[i] = curr;
    }
  }
  for (int i = 0; i < n; i++) {
    auto [a, b] = v[i];
    if (a > 0) {
      ll rem = right[i] - left[i];
      if (rem > 0) rem = max(0ll, rem - way1 - way2);
      else rem = min(0ll, rem + way1);
      if (rem == 0) return answer(true);
    }
  }

  return answer(false);
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