#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  int garbageCollection(vector<string>&garbage, vector<int>&travel) {
    int n = garbage.size();
    char type[] = {'G', 'M', 'P'};
    int ans = 0;
    for (int it = 0; it < 3; it++) {
      int len = 0;
      for (int i = 0; i < n; i++) {
        if (i) len += travel[i - 1];
        if (find(garbage[i].begin(), garbage[i].end(), type[it]) != garbage[i].end()) {
          ans += len;
          len = 0;
        }
      }
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}