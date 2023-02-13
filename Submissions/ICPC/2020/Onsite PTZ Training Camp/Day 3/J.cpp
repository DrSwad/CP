#include <bits/stdc++.h>
using namespace std;

map<string, int> s2i;
vector<string> i2s;

void init() {
  s2i["110"] = 0;
  s2i["101"] = 1;
  s2i["011"] = 2;
  s2i["001"] = 3;
  s2i["010"] = 4;
  s2i["100"] = 5;
  i2s.push_back("110");
  i2s.push_back("101");
  i2s.push_back("011");
  i2s.push_back("001");
  i2s.push_back("010");
  i2s.push_back("100");
}

vector<int> type_ids[6];
vector<pair<int, int>> ans;

void handle(int type1, int id1, int type2, int id2) {
  vector<bool> vis(4, false);
  string s1 = i2s[type1], s2 = i2s[type2];
  for (int i = 0; i < 3; i++) {
    int v = (s1[i] - '0') + (s2[i] - '0') * 2;
    vis[v] = true;
  }

  int v;
  for (v = 0; v < 4; v++) {
    if (!vis[v]) break;
  }

  bool true1 = v % 2 == 0;
  bool true2 = v / 2 == 0;

  ans.push_back({id1* (true1 ? 1 : -1), id2 * (true2 ? 1 : -1)});
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  init();

  int n;
  cin >> n;

  {
    vector<string> s(3);
    for (int i = 0; i < 3; i++) {
      cin >> s[i];
    }

    for (int i = 0; i < n; i++) {
      string ss = "";
      for (int j = 0; j < 3; j++) ss += s[j][i];
      if (ss == "000") ans.push_back({-(i + 1), -(i + 1)});
      else if (ss == "111") ans.push_back({(i + 1), (i + 1)});
      else type_ids[s2i[ss]].push_back(i + 1);
    }
  }

  for (int type = 0; type < 6; type++) {
    for (int i = 1; i < (int)type_ids[type].size(); i++) {
      int id1 = type_ids[type][i - 1];
      int id2 = type_ids[type][i];
      ans.push_back({id1, -id2});
      ans.push_back({-id1, id2});
    }
  }

  for (int type = 0; type < 3; type++) {
    if (type_ids[type].size() > 0 and type_ids[type + 3].size() > 0) {
      int id1 = type_ids[type][0];
      int id2 = type_ids[type + 3][0];
      ans.push_back({id1, id2});
      ans.push_back({-id1, -id2});
    }
  }

  {
    vector<int> type(3, -1), id(3, 0);
    for (int i = 0; i < 3; i++) {
      if (type_ids[i].size() > 0) type[i] = i, id[i] = type_ids[i][0];
      else if (type_ids[i + 3].size() > 0) type[i] = i + 3, id[i] = type_ids[i + 3][0];
    }

    for (int i = 0; i < 3; i++) {
      for (int j = i + 1; j < 3; j++) {
        if (type[i] != -1 and type[j] != -1) {
          handle(type[i], id[i], type[j], id[j]);
        }
      }
    }
  }

  cout << ans.size() << "\n";
  assert(ans.size() <= (int)2e5);
  for (auto [x, y] : ans) {
    cout << x << " " << y << "\n";
  }

  return 0;
}