#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int arithmeticTriplets(vector<int> nums, int diff) {
    int n = nums.size();
    int ans = 0;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          if (nums[j] - nums[i] == diff and nums[k] - nums[j] == diff) ans++;
        }
      }
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << Solution().arithmeticTriplets({4, 5, 6, 7, 8, 9}, 2) << "\n";

  return 0;
}