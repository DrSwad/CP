#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<pair<int, int>, null_type, less<pair<int, int>>, rb_tree_tag,
  tree_order_statistics_node_update>
  ordered_set;
// find_by_order(k) : iterator to the k'th element (0-indexed)
// order_of_key(k) : number of items strictly smaller than k

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, m;
  cin >> n >> m;

  ordered_set st;
  vector<int> t(n);
  for (int i = 0; i < n; i++) {
    t[i] = i;
    st.insert(make_pair(t[i], i));
  }

  vector<int> mn(n), mx(n);
  iota(mn.begin(), mn.end(), 0);
  iota(mx.begin(), mx.end(), 0);

  int time = -1;
  while (m--) {
    int index;
    cin >> index;
    index--;

    int position = st.order_of_key(make_pair(t[index], index));
    mn[index] = 0;
    mx[index] = max(mx[index], position);

    st.erase(st.find_by_order(position));
    t[index] = time--;
    st.insert(make_pair(t[index], index));
  }

  {
    int position = 0;
    for (auto [_, index] : st) {
      mx[index] = max(mx[index], position);
      position++;
    }
  }

  for (int i = 0; i < n; i++) {
    cout << mn[i] + 1 << " " << mx[i] + 1 << "\n";
  }

  return 0;
}