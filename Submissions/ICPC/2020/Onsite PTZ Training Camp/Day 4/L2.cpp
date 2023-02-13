#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 5e5 + 5;

void test_case() {
  int n, k;
  cin >> n >> k;

  int logk = 32 - __builtin_clz(k);

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll sum = 0;
  for (int i : a) sum += i;

  int nn = 2 * n;
  for (int i = 0; i < n; i++) {
    a.push_back(a[i]);
  }

  vector<ll> pref(nn + 1);
  pref[0] = 0;
  for (int i = 1; i <= nn; i++) {
    pref[i] = pref[i - 1] + a[i - 1];
  }

  // debug(sum, pref);

  function<bool(ll)> check = [&](ll min_len) {
    // bool flag = min_len == 341204483ll;

    vector<vector<int>> nxt(logk, vector<int>(n));

    for (int i = 0; i < n; i++) {
      ll min_pref = pref[i] + min_len;
      if (pref.back() < min_pref) nxt[0][i] = -1;
      else nxt[0][i] = lower_bound(pref.begin(), pref.end(), min_pref) - pref.begin();
    }

    // if (flag) debug(nxt[0]);

    for (int i = 1; i < logk; i++) {
      for (int j = 0; j < n; j++) {
        int k = nxt[i - 1][j];
        if (k == -1 or k >= nn) nxt[i][j] = -1;
        else {
          if (k < n) nxt[i][j] = nxt[i - 1][k];
          else nxt[i][j] = nxt[i - 1][k - n] + n;
          if (nxt[i][j] >= nn) nxt[i][j] = -1;
        }
      }
      // if (flag) debug(i, nxt[i]);
    }

    for (int i = 0; i < n; i++) {
      // bool flag2 = flag and i == 1;
      int at = i;
      int kk = k;
      for (int b = 0; b < logk and at < nn and at != -1; b++) {
        if (kk >> b & 1) {
          // if (flag2) debug(b, at);
          if (at < n) at = nxt[b][at];
          else {
            if (nxt[b][at - n] == -1) at = -1;
            else at = nxt[b][at - n] + n;
          }
          kk -= 1 << b;
        }
      }
      if (at != -1 and at <= i + n and !kk) {
        // if (flag) debug(i, at);
        return true;
      }
    }

    return false;
  };

  ll L = LLONG_MAX;
  for (int i : a) L = min(L, (ll)i);
  ll R = sum / k + 1;
  while (R > L + 1) {
    ll mid = (L + R) / 2;
    if (check(mid)) L = mid;
    else R = mid;
  }

  cout << L << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}