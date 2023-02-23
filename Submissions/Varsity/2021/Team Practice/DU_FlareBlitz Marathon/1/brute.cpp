#include <bits/stdc++.h>
using namespace std;

const int A = 2000;
const int SQRTN = 1e5;

bool check_if_possible(int n, vector<int> a) {
  int sum = accumulate(a.begin(), a.end(), 0);
  for (int mask = 1; mask < (1 << n) - 1; mask++) {
    int curr = 0;
    for (int i = 0; i < n; i++) {
      if (mask >> i & 1) curr += a[i];
    }
    if (gcd(curr, sum) > 1) return true;
  }
  return false;
}

bool check_answer(int n, vector<int> a, vector<int> ans) {
  int sum = accumulate(a.begin(), a.end(), 0);
  int curr = 0;
  for (int i : ans) curr += a[i];
  return gcd(curr, sum) > 1;
}

void answer(vector<int> ans) {
  if (ans.empty()) cout << "No\n";
  else {
    cout << "Yes\n";
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
    }
    cout << "\n";
  }
  exit(EXIT_SUCCESS);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int sum = accumulate(a.begin(), a.end(), 0);

  int p = 2;
  while (p <= SQRTN and sum % p != 0) p++;
  if (sum % p != 0) p = sum;

  vector<int> ans;
  if (sum == p) {
    assert(!check_if_possible(n, a));
    answer(ans);
  }
  else if (p < n) {
    vector<int> prefix_last_found(p, -1);
    int pref = 0;
    for (int i = 0; i < n; i++) {
      (pref += a[i]) %= p;
      if (prefix_last_found[pref] != -1) {
        int l = prefix_last_found[pref] + 1, r = i;
        for (int i = l; i <= r; i++) {
          ans.push_back(i);
        }
        assert(check_if_possible(n, a));
        assert(check_answer(n, a, ans));
        answer(ans);
      }
      prefix_last_found[pref] = i;
    }
  }
  else {
    assert(n <= A);
    vector<bitset<A*A + 1>> dp(n + 1);
    dp[0][0] = true;
    for (int i = 1; i <= n; i++) {
      dp[i] = dp[i - 1] | (dp[i - 1] << a[i - 1]);
    }

    int need = 0;
    for (int i = 1; i < sum; i++) {
      if (dp[n][i] and gcd(sum, i) > 1) {
        need = i;
      }
    }

    if (!need) {
      assert(!check_if_possible(n, a));
      answer(ans);
    }

    for (int i = n; i >= 1; i--) {
      assert(dp[i][need]);
      if (!dp[i - 1][need]) {
        ans.push_back(i - 1);
        need -= a[i - 1];
      }
    }

    assert(check_if_possible(n, a));
    assert(check_answer(n, a, ans));
    reverse(ans.begin(), ans.end());
    answer(ans);
  }

  return 0;
}