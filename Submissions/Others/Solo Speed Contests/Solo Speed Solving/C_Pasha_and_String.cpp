#include <bits/stdc++.h>
using namespace std;

int main() {
  string s;
  cin >> s;

  int m;
  scanf("%d", &m);

  vector<int> a(m);
  for (int &i : a) scanf("%d", &i), i--;

  sort(a.begin(), a.end());

  int n = s.size();
  for (int i = 0; i < n / 2; i++) {
    int cnt = upper_bound(a.begin(), a.end(), i) - a.begin();
    if (cnt % 2 == 1) swap(s[i], s[n - 1 - i]);
  }

  cout << s << "\n";

  return 0;
}