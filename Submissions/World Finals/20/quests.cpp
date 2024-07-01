/*
   XP / v < d
   <=> XP < d * v
   So, replace d[i] with (v * d[i]).

   Now, note that sum(c * x[i]) < d[j]
   <=> c * sum(x[i]) < d[j]
   <=> sum(x[i]) < ceil(d[j] / c)

   So, we set all d[i] to ceil(d[i] / c).

   All levels contribute at least x[i].
   Some 'special' levels contribute (c * x[i]).
   So, we just need to maximize sum(c * x[i]) for all special levels i.

   The special levels must be a prefix in the final ordering.
   In this prefix, we can sort the levels by (x[i] + d[i]) using exchange argument.
   So, let's sort all the levels beforehand by (x[i] + d[i]).
   In this sorted array of levels, we need to choose some special levels such that the sum(c * x[i]) is maximized for special levels i.

   Now, we do dp. Let dp[i][XP] = 1 if there exists a choice of special levels from the first i levels in the sorted array such that the sum of their XPs is XP.

   Since, sum(x[i]) <= max(x) * max(n) = 2000 * 2000, we can use a bitset of size 4e6.
 */

#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, v, c; // 1 <= n, v <= 2000, 2 <= c <= 2000
  cin >> n >> v >> c;

  vector<int> x(n), d(n); // 1 <= x[i] <= 2000, 1 <= d[i] <= 1e6
  for (int i = 0; i < n; i++) {
    cin >> x[i] >> d[i];
    d[i] = d[i] * v;
    d[i] = (d[i] + (c - 1)) / c;
  }

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(
    order.begin(),
    order.end(),
    [&](int i, int j) {
      return x[i] + d[i] < x[j] + d[j];
    }
  );

  const int sz = int(4e6) + 1;
  bitset<sz> dp;
  dp[0] = 1;

  for (int oi = 0; oi < n; oi++) {
    int i = order[oi];

    bitset<sz> pref;
    pref.set();
    pref >>= sz - d[i];

    dp = dp | ((dp & pref) << x[i]);
  }

  int max_special_sum = 0;
  for (int i = 0; i < sz; i++) {
    if (dp[i]) {
      max_special_sum = i;
    }
  }

  int ans =
    accumulate(x.begin(), x.end(), 0)
    + max_special_sum * (c - 1);

  cout << ans << "\n";

  return 0;
}