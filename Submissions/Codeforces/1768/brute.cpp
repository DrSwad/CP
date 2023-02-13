#include <bits/stdc++.h>
using namespace std;

vector<int> do_move(vector<int> p, bool right_op) {
  int n = p.size() / 3;
  if (right_op) sort(p.begin() + n, p.end());
  else sort(p.begin(), p.begin() + 2 * n);
  return p;
}

bool okay(vector<int> p) {
  return is_sorted(p.begin(), p.end());
}

int move_cnt(vector<int> p) {
  if (okay(p)) return 0;
  if (okay(do_move(p, 0)) or okay(do_move(p, 1))) return 1;
  if (okay(do_move(do_move(p, 0), 1)) or okay(do_move(do_move(p, 1), 0))) return 2;
  return 3;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, mod;
  cin >> n >> mod;

  vector<int> p(3 * n);
  iota(p.begin(), p.end(), 0);

  vector<int> d(4, 0);

  int ans = 0;
  do {
    int m = move_cnt(p);
    if (m == 1) debug(p);
    d[m]++;
    (ans += m) %= mod;
  } while (next_permutation(p.begin(), p.end()));

  debug(d);
  cout << ans << "\n";

  return 0;
}

/*
   [p]: {0, 1, 3, 2, 4, 5}
   [p]: {0, 1, 2, 3, 5, 4}
   [p]: {0, 1, 2, 4, 3, 5}
   [p]: {0, 1, 2, 4, 5, 3}
   [p]: {0, 1, 2, 5, 3, 4}
   [p]: {0, 1, 2, 5, 4, 3}
   [p]: {0, 1, 3, 2, 5, 4}
   [p]: {0, 1, 3, 4, 2, 5}
   [p]: {0, 1, 3, 4, 5, 2}
   [p]: {0, 1, 3, 5, 2, 4}
   [p]: {0, 1, 3, 5, 4, 2}
   [p]: {0, 1, 4, 2, 3, 5}
   [p]: {0, 1, 4, 2, 5, 3}
   [p]: {0, 1, 4, 3, 2, 5}
   [p]: {0, 1, 4, 3, 5, 2}
   [p]: {0, 1, 4, 5, 2, 3}
   [p]: {0, 1, 4, 5, 3, 2}
   [p]: {0, 1, 5, 2, 3, 4}
   [p]: {0, 1, 5, 2, 4, 3}
   [p]: {0, 1, 5, 3, 2, 4}
   [p]: {0, 1, 5, 3, 4, 2}
   [p]: {0, 1, 5, 4, 2, 3}
   [p]: {0, 1, 5, 4, 3, 2}
   [p]: {0, 2, 1, 3, 4, 5}
   [p]: {0, 2, 3, 1, 4, 5}
   [p]: {0, 3, 1, 2, 4, 5}
   [p]: {0, 3, 2, 1, 4, 5}
   [p]: {1, 0, 2, 3, 4, 5}
   [p]: {1, 0, 3, 2, 4, 5}
   [p]: {1, 2, 0, 3, 4, 5}
   [p]: {1, 2, 3, 0, 4, 5}
   [p]: {1, 3, 0, 2, 4, 5}
   [p]: {1, 3, 2, 0, 4, 5}
   [p]: {2, 0, 1, 3, 4, 5}
   [p]: {2, 0, 3, 1, 4, 5}
   [p]: {2, 1, 0, 3, 4, 5}
   [p]: {2, 1, 3, 0, 4, 5}
   [p]: {2, 3, 0, 1, 4, 5}
   [p]: {2, 3, 1, 0, 4, 5}
   [p]: {3, 0, 1, 2, 4, 5}
   [p]: {3, 0, 2, 1, 4, 5}
   [p]: {3, 1, 0, 2, 4, 5}
   [p]: {3, 1, 2, 0, 4, 5}
   [p]: {3, 2, 0, 1, 4, 5}
   [p]: {3, 2, 1, 0, 4, 5}
 */