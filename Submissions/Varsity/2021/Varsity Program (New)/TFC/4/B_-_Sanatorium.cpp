#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

pair<vector<ll>, ll> one_day(vector<ll> rem, int day_state) {
  ll end_state = day_state;
  auto nrem = rem;
  for (int i = 0; i < 3; i++) {
    if (day_state < (i + 1) and nrem[i]) nrem[i]--, end_state = i + 1;
  }

  if (count(nrem.begin(), nrem.end(), 0) < 3) end_state = 3;

  ll missed = 0;
  for (int i = 0; i < 3; i++) {
    if (day_state < (i + 1) and end_state >= (i + 1) and !rem[i]) missed++;
  }

  return {nrem, missed};
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<ll> rem(3);
  for (ll &i : rem) cin >> i;

  ll ans = LLONG_MAX;
  for (int day_state = 0; day_state < 4; day_state++) {
    auto [nrem, missed] = one_day(rem, day_state);

    if (count(nrem.begin(), nrem.end(), 0) < 3) {
      ll max_rem = 0;
      for (int i = 0; i < 3; i++) {
        max_rem = max(max_rem, nrem[i]);
      }

      ll passed_days = max_rem - 1;
      for (int i = 0; i < 3; i++) {
        missed += max(0ll, passed_days - nrem[i]);
        nrem[i] = max(0ll, nrem[i] - passed_days);
      }

      auto [nnrem, nmissed] = one_day(nrem, 0);
      missed += nmissed;
    }

    ans = min(ans, missed);
  }

  cout << ans << "\n";

  return 0;
}