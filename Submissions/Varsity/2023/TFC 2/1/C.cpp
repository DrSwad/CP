#include <bits/stdc++.h>
using namespace std;

const int L = 1e8;

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

  vector<int> f(2, 1);
  while (*prev(f.end()) + *prev(prev(f.end())) <= L) {
    f.push_back(*prev(f.end()) + *prev(prev(f.end())));
  }

  ordered_set st;
  priority_queue<int> pq;
  map<int, int> last;

  for (int i = 1; i < f.size(); i++) {
    st.insert(f[i]);
    pq.push(-f[i]);
    last[f[i]] = i;
  }

  while (!pq.empty()) {
    int at = pq.top();
    pq.pop();
    at = -at;

    for (int j = 0; j < f.size(); j++) {
      int k = at * f[j];
      if (k > L) break;
      if (st.find(k) == st.end()) {
        st.insert(k);
        pq.push(-k);
        last[k] = j;
      }
    }
  }

  st.insert(0);

  int t;
  cin >> t;

  while (t--) {
    int l, r, n;
    cin >> l >> r >> n;

    int low = st.order_of_key(l);
    int up = st.order_of_key(r + 1);

    if (up - low < n) {
      cout << "-1\n";
      continue;
    }

    int val = *st.find_by_order(low + n - 1);
    cout << val << " ";
    if (val == 0) {
      cout << ".##\n";
    }
    else {
      do {
        int i = last[val];
        for (int j = 0; j <= i; j++) cout << ".";
        val /= f[i];
        if (val > 1) cout << "#";
      } while (val > 1);
      cout << "\n";
    }
  }

  return 0;
}