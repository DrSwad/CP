#include <bits/stdc++.h>
using namespace std;

struct debug {
#define contPrint \
  { *this << "["; \
    int f = 0; for (auto it : x) { *this << (f?", ":""); *this << it; f = 1;} \
    *this << "]"; return *this;}

  ~debug() {cerr << endl;}
  template<class c> debug&operator<<(c x) {cerr << x; return *this;}
  template<class c, class d>
  debug&operator<<(pair<c, d> x) {
    *this << "(" << x.first << ", " << x.second << ")";
    return *this;
  }
  template<class c> debug&operator<<(vector<c> x) contPrint;
#undef contPrint
};

#define dbg(x) "[" <<#x << ": " << x << "]  "
#define Wa() cerr << "[LINE: " << __LINE__ << "] -> "; debug() <<

typedef long long ll;
const int MOD = 1e9 + 9;
const int N = 505;

int n, k;
pair<int, int> c[2 * N];
int pref[2 * N];
int dp[2][N][N];

int main() {
  freopen("input.txt", "r", stdin);
  freopen("output.txt", "w", stdout);

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    c[i] = {x, 1};
  }
  for (int i = 1; i <= n; i++) {
    int x;
    cin >> x;
    c[n + i] = {x, 0};
  }

  if (n % 2 != k % 2) {
    cout << "0\n";
    return 0;
  }

  sort(c + 1, c + 2 * n + 1);
  for (int i = 1; i <= 2 * n; i++) {
    pref[i] = pref[i - 1] + c[i].second;
  }

  dp[0][0][0] = 1;

  for (int i = 1; i <= 2 * n; i++) {
    for (int cc = 0; cc <= n; cc++) {
      for (int tc = cc; tc <= n; tc++) {
        int dpi = i & 1;
        dp[dpi][cc][tc] = 0;
        if (c[i].second == 0) {
          (dp[dpi][cc][tc] += dp[dpi ^ 1][cc][tc]) %= MOD;
          (dp[dpi][cc][tc] += (ll)(cc + 1) * dp[dpi ^ 1][cc + 1][tc] % MOD) %= MOD;
        }
        if (c[i].second == 1) {
          if (cc > 0) {
            (dp[dpi][cc][tc] += dp[dpi ^ 1][cc - 1][tc - 1]) %= MOD;
          }
          if (pref[i - 1] >= cc) {
            int available = (i - 1) - cc - 2 * (pref[i - 1] - cc);
            if (available >= 0) {
              (dp[dpi][cc][tc] += (ll)available * dp[dpi ^ 1][cc][tc] % MOD) %= MOD;
            }
          }
        }
      }
    }
  }

  cout << dp[0][0][(n - k) / 2] << endl;

  return 0;
}