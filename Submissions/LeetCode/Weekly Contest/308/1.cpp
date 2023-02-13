#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
  vector<int> answerQueries(vector<int>&nums, vector<int>&queries) {
    int n = nums.size();
    int m = queries.size();

    sort(nums.begin(), nums.end());

    vector<long long> pref(n + 1);
    pref[0] = 0;
    for (int i = 0; i < n; i++) {
      pref[i + 1] = pref[i] + nums[i];
    }

    vector<int> ans;
    for (int q : queries) {
      ans.push_back(upper_bound(pref.begin(), pref.end(), (long long)q) - pref.begin() - 1);
    }

    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}