#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
  string removeStars(string s) {
    string ans;
    for (char c : s) {
      if (c == '*') ans.pop_back();
      else ans += c;
    }
    return ans;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  return 0;
}