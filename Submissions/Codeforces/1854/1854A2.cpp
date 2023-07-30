#include <bits/stdc++.h>
using namespace std;

void solve1(vector<int> &a, vector<pair<int, int>> &ans) {
  int n = a.size();

  {
    int max_i = 0;
    for (int i = 1; i < n; i++) {
      if (abs(a[i]) > abs(a[max_i])) max_i = i;
    }

    for (int i = 0; i < n; i++) {
      if (a[i] != 0 and a[i] / abs(a[i]) != a[max_i] / abs(a[max_i])) {
        ans.emplace_back(i, max_i);
        a[i] += a[max_i];
      }
    }
  }

  if (*min_element(a.begin(), a.end()) >= 0) {
    for (int i = 1; i < n; i++) {
      ans.emplace_back(i, i - 1);
      a[i] += a[i - 1];
    }
  }
  else {
    for (int i = n - 2; i >= 0; i--) {
      ans.emplace_back(i, i + 1);
      a[i] += a[i + 1];
    }
  }
}

void solve2(vector<int> &a, vector<pair<int, int>> &ans) {
  int n = a.size();

  int pos = 0, neg = 0;

  for (int i = 0; i < n; i++) {
    if (a[i] > 0) pos++;
    else if (a[i] < 0) neg++;
  }

  if (pos == 0 and neg == 0) return;

  int i;
  for (i = 0; i < n; i++) {
    if (pos >= neg and a[i] > 0) break;
    if (neg > pos and a[i] < 0) break;
  }

  for (int j = 0; j < 5; j++) {
    ans.emplace_back(i, i);
    a[i] += a[i];
  }

  solve1(a, ans);
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int pos = 0, neg = 0, zero = 0;

  vector<pair<int, int>> ans;

  for (int i = 0; i < n; i++) {
    if (a[i] > 0) pos++;
    else if (a[i] < 0) neg++;
    else zero++;
  }

  if (min(pos + zero, neg + zero) > 7) solve1(a, ans);
  else solve2(a, ans);

  cout << ans.size() << "\n";
  for (auto [i, j] : ans) cout << i + 1 << " " << j + 1 << "\n";
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