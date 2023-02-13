#include <bits/stdc++.h>

using namespace std;

bool can(string target, string s, string t) {
  vector<int> t_pos[30], s_pos[30];
  for (int i = 0; i < t.size(); i++) {
    t_pos[t[i] - 'a'].push_back(i);
  }
  for (int i = 0; i < s.size(); i++) {
    s_pos[s[i] - 'a'].push_back(i);
  }

  int n = target.size();
  int tn = t.size(), sn = s.size();

  for (int i = 0; i < 26; i++) {
    s_pos[i].push_back(sn);
    t_pos[i].push_back(tn);
  }

  int turn = 0;
  int tLast = -1, sLast = -1;
  bool flag = true;
  for (int i = 0; i < n; i++) {
    int c = target[i] - 'a';
    if (turn) {
      int pos = *upper_bound(t_pos[c].begin(), t_pos[c].end(), tLast);
      if (pos == tn) {
        flag = false; break;
      }
      tLast = pos;
    } else {
      int pos = *upper_bound(s_pos[c].begin(), s_pos[c].end(), sLast);
      if (pos == sn) {
        flag = false; break;
      }
      sLast = pos;
    }

    turn ^= 1;
  }

  return flag;
}

int main() {

  string s, t;
  cin >> s >> t;

  if (can(s, s, t) or can(s, t, s)) {
    cout << "Yes\n";
  } else {
    cout << "No\n";
  }

  return 0;
}