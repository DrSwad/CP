#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int m, n, k;
    scanf("%d %d %d", &m, &n, &k);

    int totTypes = 0;
    map<string, int> pieceType;
    vector<string> types;

    vector<int> seq;
    char s[11];
    for (int i = 0; i < m; i++) {
      scanf("%s", s);

      int type;
      if (pieceType.find(s) == pieceType.end()) {
        type = pieceType.size();
        pieceType[s] = type;
        types.push_back(s);
        totTypes++;
      } else {
        type = pieceType[s];
      }

      seq.push_back(type);
    }

    vector<vector<vector<int>>> typePos(totTypes, vector<vector<int>>(3));
    map<int, bool> posVis;
    for (int i = 0; i < n; i++) posVis[i] = true;

    // debug() << name(seq);

    for (int i = 0; i < m; i++) {
      int type = seq[i];
      int level = 0;
      // debug() << name(i) name(type);

      if (!typePos[type][2].empty()) continue;

      while (level < 2 and typePos[type][level].size() == k - 1) {
        for (int pos : typePos[type][level]) { posVis[pos] = true; }
        typePos[type][level].clear();
        level++;
      }

      // debug() << name(typePos);
      // debug() << name(posVis);

      if (posVis.empty()) continue;

      typePos[type][level].push_back(posVis.begin()->first);
      posVis.erase(posVis.begin());
    }

    vector<string> ans(n, "-1");
    for (int type = 0; type < totTypes; type++) {
      for (int level = 0; level < 3; level++) {
        for (int pos : typePos[type][level]) {
          ans[pos] = level ? types[type] + to_string(level + 1) : types[type];
        }
      }
    }

    printf("Case %d:", cs);
    for (int i = 0; i < n; i++) printf(" %s", ans[i].c_str());
    puts("");
  }

  return 0;
}
