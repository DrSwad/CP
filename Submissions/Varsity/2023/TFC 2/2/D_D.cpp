#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int digits = 18;
const int mod = 1e9 + 7;
const int max_n = 8;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int n;
bool s[max_n];
ll x[max_n];
vector mask_change_ways(1 << max_n, vector(1 << max_n, 0));

int DP(int at, int state) {
  if (at == digits) {}
  return 0;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 0; i < n; i++) {
    cin >> s[i] >> x[i];
  }

  mask_change_ways[0][0] = 1;
  for (int i = 0; i < n; i++) {
    vector cur_change_ways(2, vector(2, 0));
    for (int cur_state = 0; cur_state < 2; cur_state++) {
      for (int d = 0; d <= 9; d++) {
        int new_state;
        if (s[i] == 0 and d <);
      }
    }
  }

  return 0;
}