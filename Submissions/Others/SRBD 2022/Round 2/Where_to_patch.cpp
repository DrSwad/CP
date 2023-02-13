#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  while (cin >> n) {
    vector<pair<int, int>> v;
    for (int i = 0; i < n; i++) {
      int p, id;
      cin >> p >> id;
      v.push_back({p, id});
    }

    sort(v.begin(), v.end());

    int q;
    cin >> q;

    while (q--) {
      int x;
      cin >> x;

      int ans_val = INT_MAX, ans_id = -1;
      auto p_it = lower_bound(v.begin(), v.end(), make_pair(x, INT_MIN));
      if (p_it != v.end()) {
        pair<int, int> p = *p_it;
        assert(p.first >= x);
        if (p.first - x < ans_val or (p.first - x == ans_val and p.second < ans_id)) {
          ans_val = p.first - x, ans_id = p.second;
        }
      }
      if (p_it != v.begin()) {
        pair<int, int> p = *prev(p_it);
        assert(p.first < x);
        if (x - p.first < ans_val or (x - p.first == ans_val and p.second < ans_id)) {
          ans_val = x - p.first, ans_id = p.second;
        }
      }
      assert(ans_id != -1);

      cout << ans_id << "\n";
    }
  }

  return 0;
}