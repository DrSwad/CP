#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;
// find_by_order(k) : iterator to the k'th element (0-indexed)
// order_of_key(k) : number of items strictly smaller than k
// auto cmp = [](int a, int b) { return a < b; };
// tree<int, null_type, decltype(cmp)> x(cmp);
// tree<int, null_type, function<bool(int, int)>> y(
//     [](int a, int b) { return a < b; });

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> l(n), r(n);
  {
    ordered_set os;
    for (int i = 0; i < n; i++) {
      l[i] = os.order_of_key(a[i]);
      if (l[i] < os.size()) os.erase(os.find_by_order(l[i]));
      os.insert(a[i]);
    }
  }
  {
    ordered_set os;
    for (int i = n - 1; i >= 0; i--) {
      r[i] = os.order_of_key(-a[i]);
      if (r[i] < os.size()) os.erase(os.find_by_order(r[i]));
      os.insert(-a[i]);
    }
  }

  int lis = 0;
  for (int i = 0; i < n; i++) {
    lis = max(lis, l[i] + r[i] + 1);
  }

  vector<bool> has_lis(n);
  for (int i = 0; i < n; i++) {
    has_lis[i] = lis == l[i] + r[i] + 1;
  }

  vector<bool> pos = has_lis;
  for (int i = 0, mx = 0; i < n; i++) {
    if (mx > a[i]) pos[i] = false;
    if (has_lis[i]) mx = max(mx, a[i]);
  }
  for (int i = n - 1, mn = n + 1; i >= 0; i--) {
    if (mn < a[i]) pos[i] = false;
    if (has_lis[i]) mn = min(mn, a[i]);
  }

  vector<int> ans;
  for (int i = 0; i < n; i++) {
    if (pos[i]) ans.push_back(a[i]);
  }

  sort(ans.begin(), ans.end());

  if (ans.empty()) cout << "-1\n";
  else {
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i];
    }
    cout << "\n";
  }

  return 0;
}