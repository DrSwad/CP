#include <bits/stdc++.h>
using namespace std;

const int MOD = 998244353;

int solve(int n, int k, vector<deque<int>> &v) {
  if (n == 1) return 1;
  int mul = 0;
  int val = -1;

  {
    int x = v[0].front();
    int cnt = 0;
    for (int i = 0; i < k; i++) {
      cnt += v[i].front() == x or v[i].back() == x;
    }
    if (cnt >= k) {
      mul++;
      val = v[0].front();
    }
  }

  {
    int x = v[0].back();
    int cnt = 0;
    for (int i = 0; i < k; i++) {
      cnt += v[i].front() == x or v[i].back() == x;
    }
    if (cnt >= k) {
      mul++;
      val = v[0].back();
    }
  }

  if (mul) {
    for (int i = 0; i < k; i++) {
      if (v[i].front() == val) v[i].pop_front();
      else v[i].pop_back();
    }
  }

  return mul * 1ll * solve(n - 1, k, v) % MOD;
}

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<deque<int>> v(k);
  for (int i = 0; i < k; i++) {
    for (int j = 0; j < n; j++) {
      int x;
      cin >> x;
      v[i].push_back(x);
    }
  }

  cout << solve(n, k, v) << "\n";
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