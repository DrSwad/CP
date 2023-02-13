#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int edgeScore(vector<int> edges) {
    int n = edges.size();
    vector<long long> score(n, 0);
    for (int i = 0; i < n; i++) score[edges[i]] += i;
    long long mx = *max_element(score.begin(), score.end());
    return find(score.begin(), score.end(), mx) - score.begin();
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << Solution().edgeScore({1, 0, 0, 0, 0, 7, 7, 5}) << "\n";

  return 0;
}