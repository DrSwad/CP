#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  cin.ignore();

  int blk_sz = sqrt(n);
  int tot_blk = (n + blk_sz - 1) / blk_sz;

  vector<vector<int>> day_precalc(n + 1);
  day_precalc[0] = vector<int>(tot_blk, 0);
  vector<int> add(n), rem(n);

  for (int d = 1; d <= n; d++) {
    day_precalc[d] = day_precalc[d - 1];

    string line;
    getline(cin, line);
    stringstream ss(line);

    char sign;
    int id;
    while (ss >> sign) {
      if (sign != '+' and sign != '-') continue;
      ss >> id;
      if (sign == '+') add[id] = d;
      else rem[id] = d;

      for (int blk = id / blk_sz; blk >= 0; blk--) {
        day_precalc[d][blk] += sign == '+' ? 1 : -1;
      }
    }
  }

  int x = 0;
  for (int i = 1; i <= n; i++) {
    int d;
    cin >> d;

    int nx = x;
    int blk = x == 0 ? 0 : (x - 1) / blk_sz + 1;
    if (blk < tot_blk) nx += day_precalc[d][blk];

    int st = min(n, blk * blk_sz);
    for (int id = x; id < st; id++) {
      nx += add[id] <= d and rem[id] > d;
    }

    x = nx % n;
  }

  cout << x << "\n";

  return 0;
}