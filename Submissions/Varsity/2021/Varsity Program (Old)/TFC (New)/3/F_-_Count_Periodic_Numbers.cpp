#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int till(int mx) {
  int ret = 0;
  for (int period = 1; period <= 32; period++) {
    ll mask = (1ll << period) - 1;
    ll curr_val = mask;
    int curr_cnt = 0;
    while (curr_val <= mx) {
      curr_cnt++;
      curr_val <<= period;
      if ((curr_val >> period & 1) == 0) curr_val += mask;
    }
    ret += curr_cnt;
  }
  return ret;
}

void test_case() {
  int l, r;
  cin >> l >> r;
  cout << till(r) - till(l - 1) << "\n";
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