#include <bits/stdc++.h>
using namespace std;

vector<int> fillSpace(int space, int flex) {
  if (space == 0) return {-1};
  else if (space == -1) return {};
  else if (space < -1) return {-1};
  else {
    if (flex == 0) return {-1};
    vector<int> ret((space + 1) / 2, 1);
    if (space % 2 == 0) {
      if (flex < 2) return {-1};
      else ret.back()++;
    }
    return ret;
  }
}

inline bool isBad(vector<int> v) {
  return !v.empty() and v.back() == -1;
}

vector<int> tryFlex(vector<int> spaces, vector<int> blocks, int flex) {
  assert(spaces.size() == blocks.size() + 1);
  if (!accumulate(blocks.begin(), blocks.end(), 0)) return {};
  if (!accumulate(spaces.begin(), spaces.end(), 0)) return blocks;

  spaces[0] -= flex + 1;
  spaces.back() -= flex + 1;
  for (int i = 1; i < spaces.size() - 1; i++) {
    spaces[i] -= flex + 2;
  }

  vector<int> ans;
  for (int i = 0; i < spaces.size(); i++) {
    vector<int> got = fillSpace(spaces[i], flex);
    if (isBad(got)) return {-1};
    if (i < blocks.size()) got.push_back(blocks[i] + flex);
    for (int x : got) ans.push_back(x);
  }

  return ans;
}

void printAns(vector<int> ans) {
  printf("%d\n", (int)ans.size());
  for (int i = 0; i < ans.size(); i++) {
    if (i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");
}

int main() {
  string s;
  cin >> s;
  int n = s.length();

  vector<int> spaces, blocks;
  int at = 0;

  while (at < n) {
    spaces.push_back(0);
    while (at < n and s[at] == '_') {
      spaces.back()++;
      at++;
    }

    blocks.push_back(0);
    while (at < n and s[at] == '#') {
      blocks.back()++;
      at++;
    }
  }

  if (!blocks.empty()) {
    if (blocks.back()) spaces.push_back(0);
    else blocks.pop_back();
  }

  for (int flex = 0; flex <= 10; flex++) {
    vector<int> ans = tryFlex(spaces, blocks, flex);
    if (isBad(ans)) continue;
    printAns(ans);
    return 0;
  }

  puts("-1");

  return 0;
}