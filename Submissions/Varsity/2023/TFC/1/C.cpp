#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  vector<int> p(n);
  for (int &i : p) cin >> i;

  ordered_set os;
  for (int i = 0; i < k; i++) {
    os.insert(p[i]);
  }

  int L;
  {
    L = 0;
    auto it = os.begin();
    while (L < k and p[L] == *it) L++, it++;
  }
  int R;
  {
    R = k - 1;
    auto it = prev(os.end());
    while (R >= 0 and p[R] == *it) R--, it--;
  }

  set<pair<int, int>> st;
  if (R < L) L = R = -1;
  st.insert({L, R});

  for (int l = 1; l + k <= n; l++) {
    int r = l + k - 1;
    os.erase(p[l - 1]);
    os.insert(p[r]);

    if (L == -1 or R == -1) {
      if (p[r] != *prev(os.end())) {
        int at = os.order_of_key(p[r]);
        L = l + at;
        R = r;
      }
    }
    else {
      if (p[r] != *prev(os.end())) {
        int at = os.order_of_key(p[r]);
        L = min(L, l + at);
        R = max(R, r);
      }

      if (L < l) {
        assert(L == l - 1);
        L++;
        auto it = os.begin();
        while (L < l + k and p[L] == *it) L++, it++;
        if (R < L) L = R = -1;
        else {
          it = os.find_by_order(R - l);
          while (R >= l and p[R] == *it) R--, it--;
          if (R < L) L = R = -1;
        }
      }
    }

    st.insert({L, R});
  }

  cout << st.size() << "\n";

  return 0;
}