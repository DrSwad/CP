#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int K = 5, N = 1 << K;
const int MOD = 998244353;

int k, A, h;
int n;
ll pow_a[N + 1];
vector<pair<vector<int>, ll>> swap_options;

void constructSwapOptions(int level, vector<int> &picked_options, ll rem) {
  if (level < 0) {
    reverse(picked_options.begin(), picked_options.end());
    swap_options.push_back({picked_options, rem});
    reverse(picked_options.begin(), picked_options.end());
    return;
  }

  picked_options.push_back(0);
  int players = 1 << level;
  int eliminations = (players + 1) / 2;
  int rank = players / 2 + 1;
  ll add = 0;

  while (picked_options.back() <= eliminations) {
    ll nrem = rem + add;
    if (nrem >= MOD) nrem -= MOD;
    constructSwapOptions(level - 1, picked_options, nrem);

    picked_options.back()++;
    add += pow_a[rank] - pow_a[n / 2 + 1];
    if (add >= MOD) add -= MOD;
    if (add < 0) add += MOD;
  }
  picked_options.pop_back();
}

void checkResult(vector<int> &pos) {
  ll rem = 0;
  for (int i = 0; i < n; i++) {
    rem += (ll)(i + 1) * pow_a[pos[i]] % MOD;
    if (rem >= MOD) rem -= MOD;
  }

  for (auto [option, r] : swap_options) {
    int nrem = rem + r;
    if (nrem >= MOD) nrem -= MOD;
    if (nrem == h) {
      for (int i = 0; i < n; i += 2) {
        int level = pos[i] == 1 ? 0 : __builtin_ctz(pos[i] - 1) + 1;
        if (option[level]) {
          swap(pos[i], pos[i + 1]);
          option[level]--;
        }
      }
      assert(accumulate(option.begin(), option.end(), 0) == 0);

      for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << pos[i];
      }
      cout << "\n";

      exit(EXIT_SUCCESS);
    }
  }
}

void simulate(int level, vector<int> players, vector<int> &pos) {
  if (level == 0) {
    pos[players.back()] = 1;
    checkResult(pos);
    return;
  }

  int tot = 1 << level;
  int games = tot / 2;
  int rank = tot / 2 + 1;

  for (int mask = 0; mask < 1 << games; mask++) {
    vector<int> nplayers;
    for (int i = 0; i < games; i++) {
      if (mask >> i & 1) {
        pos[players[i << 1 | 1]] = rank;
        nplayers.push_back(players[i << 1]);
      } else {
        pos[players[i << 1]] = rank;
        nplayers.push_back(players[i << 1 | 1]);
      }
    }
    simulate(level - 1, nplayers, pos);
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> k >> A >> h;
  n = 1 << k;

  pow_a[0] = 1;
  for (int i = 1; i <= n; i++) {
    pow_a[i] = pow_a[i - 1] * A % MOD;
  }

  vector<int> picked_options;
  constructSwapOptions(k - 1, picked_options, 0);

  vector<int> pos(n), players;
  for (int i = 0; i < n; i++) {
    if (i % 2 == 1) pos[i] = n / 2 + 1;
    else players.push_back(i);
  }

  simulate(k - 1, players, pos);

  cout << "-1\n";

  return 0;
}