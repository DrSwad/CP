#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  string s;
  cin >> s;

  if (s.length() == 1) cout << "1\n";
  else {
    string ss = s + s;
    string t1 = s.substr(0, (int)s.length() - 1);
    reverse(t1.begin(), t1.end());
    string t2 = s.substr(1, (int)s.length() - 1);
    reverse(t2.begin(), t2.end());
    if (ss.find(t1) != string::npos and ss.find(t2) != string::npos) cout << "1\n";
    else cout << "0\n";
  }

  return 0;
}