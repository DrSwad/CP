#include <bits/stdc++.h>
using namespace std;

vector<int> digits(int n, int k) {
  vector<int> ret;
  while (n) {
    ret.push_back(n % k);
    n /= k;
  }
  reverse(ret.begin(), ret.end());
  return ret;
}

int brute(int n, int k) {
  vector<pair<vector<int>, int>> nums;
  for (int i = 1; i <= n; i++) {
    nums.emplace_back(digits(i, k), i);
  }

  sort(nums.begin(), nums.end());

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += nums[i - 1].second == i;
  }

  return ans;
}

void test_case() {
  int n, k;
  cin >> n >> k;
  cout << brute(n, k) << "\n";
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