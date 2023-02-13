#include <bits/stdc++.h>
using namespace std;

const int N = 16;
const int MOD = 1e9 + 7;
typedef long long ll;

int n;
int f[N][6];
unordered_map<int, int> mul_freq[2];

ll binExp(ll a, ll e, ll m = MOD) {
  if (e == -1) e = m - 2;
  ll ret = 1;
  while (e) {
    if (e & 1) ret = ret * a % m;
    a = a * a % m, e >>= 1;
  }
  return ret;
}

void backtrack(int at_dice, int end_at_dice, int map_index, ll current_mul) {
  if (at_dice == end_at_dice) {
    mul_freq[map_index][current_mul]++;
    return;
  }

  for (int i = 0; i < 6; i++) {
    backtrack(at_dice + 1, end_at_dice, map_index, current_mul * f[at_dice][i] % MOD);
  }
}

void test_case() {
  mul_freq[0].clear();
  mul_freq[1].clear();

  cin >> n;
  int x;
  cin >> x;

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 6; j++) {
      cin >> f[i][j];
    }
  }

  backtrack(0, min(n, 7), 0, 1);
  backtrack(min(n, 7), n, 1, 1);

  long long ans = 0;

  for (auto [mul1, freq1] : mul_freq[0]) {
    int mul2 = (ll)x * binExp(mul1, -1) % MOD;
    if (mul_freq[1].find(mul2) != mul_freq[1].end()) {
      ans += (long long)mul_freq[0][mul1] * mul_freq[1][mul2];
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}