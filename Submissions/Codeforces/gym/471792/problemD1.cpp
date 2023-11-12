#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  cin >> n;

  vector<tuple<int, int, int>> op(n);
  for (auto & [type, score, val] : op) {
    string type_s;
    cin >> type_s;

    if (type_s == "push") type = 1, cin >> val >> score;
    else type = -1, cin >> score;
  }

  vector max_score(n, vector(n, 0ll));

  {
    vector<int> v1, v2;
    for (int r = 0; r < n; r++) {
      if (get<0>(op[r]) == 1 and get<1>(op[r]) > 0) v1.push_back(get<1>(op[r]));
      else if (get<0>(op[r]) == -1) v2.push_back(get<1>(op[r]));

      sort(v1.begin(), v1.end(), greater<int>());
      sort(v2.begin(), v2.end(), greater<int>());

      ll cur_score = 0;
      for (int i = 0; i < v2.size(); i++) {
        ll s1 = v1.size() > i ? v1[i] : 0;
        if (s1 + v2[i] > 0) {
          cur_score += s1 + v2[i];
        }
        else break;
      }
      max_score[0][r] = cur_score;
    }
  }

  for (int l = 1; l < n; l++) {
    multiset<int> available_pushes, pops_so_far;
    ll cur_score = 0;

    for (int r = l; r < n; r++) {
      auto [type, score, val] = op[r];
      if (type == 1) {
        if (score > 0) available_pushes.insert(score);
      }
      else {
        if (!available_pushes.empty() and (*available_pushes.rbegin() + score) > 0) {
          cur_score += *available_pushes.rbegin() + score;
          available_pushes.erase(prev(available_pushes.end()));
          pops_so_far.insert(score);
        }
        else if (!pops_so_far.empty() and * pops_so_far.begin() < score) {
          cur_score += score - *pops_so_far.begin();
          pops_so_far.erase(pops_so_far.begin());
          pops_so_far.insert(score);
        }
      }

      max_score[l][r] = cur_score;
    }
  }

  ll ans = max_score[0][n - 1];
  vector dp(n, 0ll);
  for (int i = 0; i < n; i++) {
    if (get<0>(op[i]) == 1) {
      for (int j = -1; j < i; j++) {
        if (j == -1 or (get<0>(op[j]) == 1 and get<2>(op[j]) <= get<2>(op[i]))) {
          ll prv_dp = j == -1 ? 0 : dp[j];
          ll mid_clear = i == 0 ? 0 : i == j + 1 ? 0 : max_score[j + 1][i - 1];
          dp[i] = max(dp[i], prv_dp + mid_clear + get<1>(op[i]));
        }
      }
      ans = max(ans, dp[i] + (i < n - 1 ? max_score[i + 1][n - 1] : 0));
    }
  }

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}