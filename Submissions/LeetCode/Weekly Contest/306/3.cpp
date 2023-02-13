#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  string smallestNumber(string pattern) {
    int n = pattern.size();
    string p(n + 1, '0');
    iota(p.begin(), p.end(), '1');
    do {
      string curr_pattern;
      for (int i = 0; i < n; i++) {
        if (p[i] < p[i + 1]) curr_pattern += 'I';
        else curr_pattern += 'D';
      }
      if (curr_pattern == pattern) break;
    } while (next_permutation(p.begin(), p.end()));
    return p;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << Solution().smallestNumber("DDD") << "\n";

  return 0;
}