#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  string s, t;
  cin >> s >> t;

  map<char, vector<int>> mps;
  for (int i = 0; i < s.length(); i++) mps[s[i]].push_back(i);
  vector<vector<int>> vvs;
  for (auto [c, v] : mps) vvs.push_back(v);
  sort(vvs.begin(), vvs.end());

  map<char, vector<int>> mpt;
  for (int i = 0; i < t.length(); i++) mpt[t[i]].push_back(i);
  vector<vector<int>> vvt;
  for (auto [c, v] : mpt) vvt.push_back(v);
  sort(vvt.begin(), vvt.end());

  puts(vvs == vvt ? "Yes" : "No");

  return 0;
}