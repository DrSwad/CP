#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void get_permutation(int n, ll k, int st, vector<int> &ans) {
  if (n < 0) return;
  else if ((ll)(n + 1) * (n + 2) / 2 < k) ans.clear();
  else if (k < n + 1) ans.clear();
  else {
    if (k >= (n + 1) + n) {
      get_permutation(n - 1, k - (n + 1), st + 1, ans);
      ans.push_back(st);
    }
    else {
      int need = k - (n + 1);
      ans.push_back(st + need);
      for (int i = 0; i <= n; i++) {
        if (i != need) {
          ans.push_back(st + i);
        }
      }
    }

    if (st == 0) reverse(ans.begin(), ans.end());
  }
}

ll perm_func(vector<int> &p) {
  int n = p.size();
  vector<ll> A(2, 0);
  for (int it = 0; it < 2; it++) {
    int mex = 0;
    vector<bool> vis(n, false);

    for (int i = 0; i < n; i++) {
      vis[p[i]] = true;
      while (vis[mex]) mex++;
      A[it] += mex;
    }

    reverse(p.begin(), p.end());
  }
  return abs(A[0] - A[1]);
}

vector<int> brute(int n, ll k) {
  vector<int> p(n + 1);
  iota(p.begin(), p.end(), 0);
  do {
    if (perm_func(p) == k) {
      return p;
    }
  } while (next_permutation(p.begin(), p.end()));
  return {};
}

void test_case() {
  int n;
  ll k;
  cin >> n >> k;

  vector<int> ans;
  if (n <= 5) ans = brute(n, k);
  else {
    if (k >= n) get_permutation(n - 1, k, 0, ans);
    else if (k == n - 1) {
      for (int i = 1; i <= n - 3; i++) ans.push_back(i);
      ans.push_back(n);
      ans.push_back(0);
      ans.push_back(n - 2);
      ans.push_back(n - 1);
    }
    else if (k == n - 2) {
      for (int i = 1; i <= n - 3; i++) ans.push_back(i);
      ans.push_back(n - 1);
      ans.push_back(0);
      ans.push_back(n);
      ans.push_back(n - 2);
    }
    else {
      int need = (n - 1) - k;
      for (int i = 1; i <= n; i++) {
        if (i != need) ans.push_back(i);
      }
      ans.push_back(0);
      ans.push_back(need);
    }
  }

  if (ans.empty()) {
    cout << "-1\n";
  }
  else {
    if (n > 5 and k >= n) {
      for (int &i : ans) i++;
      ans.insert(ans.begin(), 0);
    }
    for (int i = 0; i <= n; i++) {
      if (i) cout << " ";
      cout << ans[i];
    }
    cout << "\n";
  }
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