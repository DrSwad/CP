#include <bits/stdc++.h>
using namespace std;

const int C = 1e6;
const int SZ = 330;

int pyramid_cnt;
vector<int> pyramid_coins;
vector<int> pyramid_base;
vector<bool> pyramid_type;
vector<int> pyramid_order;
bool possible[C + 1];
bool take[SZ][C + 1];

void init_pyramids() {
  for (int base = 2, coins = 5; coins <= C; base++, coins += base * base) {
    pyramid_coins.push_back(coins);
    pyramid_base.push_back(base);
    pyramid_type.push_back(1);
  }

  for (int base = 3, coins = 10; coins <= C; base += 2, coins += base * base) {
    pyramid_coins.push_back(coins);
    pyramid_base.push_back(base);
    pyramid_type.push_back(0);
  }

  for (int base = 4, coins = 20; coins <= C; base += 2, coins += base * base) {
    pyramid_coins.push_back(coins);
    pyramid_base.push_back(base);
    pyramid_type.push_back(0);
  }

  pyramid_cnt = pyramid_coins.size();
  pyramid_order.resize(pyramid_cnt);
  iota(pyramid_order.begin(), pyramid_order.end(), 0);
  sort(
    pyramid_order.begin(),
    pyramid_order.end(),
    [&](int i, int j) {
    return make_pair(pyramid_coins[i], pyramid_type[i]) < make_pair(pyramid_coins[j], pyramid_type[j]);
  }
    );
}

void init_dp() {
  vector<int> dp(C + 1, -1);
  dp[0] = 0;
  possible[0] = true;

  for (int i = 0; i < pyramid_cnt; i++) {
    int id = pyramid_order[i];
    vector<int> ndp = dp;
    for (int coins = 0; coins <= C; coins++) {
      if (pyramid_coins[id] <= coins) {
        int rem_coins = coins - pyramid_coins[id];
        if (dp[rem_coins] != -1 and (dp[coins] == -1 or dp[coins] >= 1 + dp[rem_coins])) {
          ndp[coins] = 1 + dp[rem_coins];
          possible[coins] = true;
          take[i][coins] = true;
        }
      }
    }
    swap(dp, ndp);
  }
}

int main() {
  // freopen("in_J.txt", "r", stdin);

  init_pyramids();
  init_dp();

  int coins;
  for (int cs = 1; ; cs++) {
    cin >> coins;
    if (!coins) break;
    cout << "Case " << cs << ":";

    if (!possible[coins]) {
      cout << " impossible\n";
    }
    else {
      for (int i = SZ - 1; i >= 0; i--) {
        if (take[i][coins]) {
          int id = pyramid_order[i];
          cout << " " << pyramid_base[id];
          cout << (pyramid_type[id] ? "H" : "L");
          coins -= pyramid_coins[id];
        }
      }
      cout << "\n";
    }
  }

  return 0;
}