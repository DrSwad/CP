#include <bits/stdc++.h>
using namespace std;

int main() {
  string s, t;
  getline(cin, s);
  getline(cin, t);

  int sn = s.length(), tn = t.length();
  vector<int> snxt(sn, sn), tnxt(tn, tn);
  for (int i = sn - 2; ~i; i--) {
    snxt[i] = s[i] == s[i + 1] ? snxt[i + 1] : i + 1;
  }
  for (int i = tn - 2; ~i; i--) {
    tnxt[i] = t[i] == t[i + 1] ? tnxt[i + 1] : i + 1;
  }

  map<char, int> vis;
  for (int i = 0, j = 0; i < sn and j < tn; ) {
    if (snxt[i] - i != tnxt[j] - j) vis[s[i]]++;
    i = snxt[i], j = tnxt[j];
  }

  for (auto [ch, freq] : vis) {
    printf("%c", ch);
  }
  puts("");

  return 0;
}