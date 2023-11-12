#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;

struct DS {
  int w;
  int sum;
  ordered_set os;
  int index;
  DS(int w) : w(w), sum(0), index(0) {}
  void insert(int val) {
    pair<int, int> cur{val, index++};
    int last = ((int)os.size() + 1) - w;
    if ((int)os.order_of_key(cur) >= last) {
      sum += val / 2;
      if (last - 1 >= 0) {
        sum -= os.find_by_order(last - 1)->first / 2;
      }
    }
    os.insert(cur);
  }
  void remove(int val) {
    int at = os.order_of_key(make_pair(val, 0));
    int last = (int)os.size() - w;
    if (at >= last) {
      sum -= val / 2;
      if (last - 1 >= 0) {
        sum += os.find_by_order(last - 1)->first / 2;
      }
    }
    os.erase(os.find_by_order(at));
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, w, k;
  cin >> n >> w >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> t(n);
  for (int &i : t) cin >> i;

  DS ds(w);

  int ans = 0;
  for (int l = 0, r = -1, sum_t = 0, sum_a = 0; l < n; ) {
    r = max(r, l - 1);

    while (r + 1 < n) {
      int new_sum_a = sum_a + a[r + 1];
      int new_sum_t = sum_t + t[r + 1];
      ds.insert(t[r + 1]);
      if (new_sum_t - ds.sum > k) {
        ds.remove(t[r + 1]);
        break;
      }
      sum_a = new_sum_a;
      sum_t = new_sum_t;
      r++;
    }

    ans = max(ans, sum_a);

    if (r >= l) {
      sum_a -= a[l];
      sum_t -= t[l];
      ds.remove(t[l]);
    }
    l++;
  }

  cout << ans << "\n";

  return 0;
}