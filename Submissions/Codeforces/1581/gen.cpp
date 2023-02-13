#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
typedef tree<int, null_type, less<int>, rb_tree_tag,
    tree_order_statistics_node_update>
    ordered_set;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 10;

  int n = rnd.next(N) + 1;
  int m = rnd.next(N) + 1;
  cout << n << " " << m << "\n";

  for (int i = 1; i <= n; i++) {
    int tot = rnd.next(N - 1) + 2;
    int x = rnd.next(tot - 1) + 1;
    int y = tot - x;
    cout << x << " " << y << "\n";
  }

  ordered_set t[2];
  for (int i = 1; i <= n; i++) t[0].insert(i);

  while (m--) {
    int op = t[0].empty() ? 2 : t[1].empty() ? 1 : rnd.next(2) + 1;
    int k = *t[op - 1].find_by_order(rnd.next(t[op - 1].size()));
    t[op - 1].erase(k);
    t[(op - 1) ^ 1].insert(k);
    cout << op << " " << k << "\n";
  }

  return 0;
}