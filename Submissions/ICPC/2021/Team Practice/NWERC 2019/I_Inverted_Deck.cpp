#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> v(n);
  for (int &i : v) cin >> i;

  v.insert(v.begin(), 0);
  v.push_back(int(1e9) + 1);

  int st;
  for (st = 0; st < n; st++) {
    if (v[st] > v[st + 1]) break;
  }
  while (v[st] == v[st - 1]) st--;

  int en;
  for (en = n + 1; en > 1; en--) {
    if (v[en] < v[en - 1]) break;
  }
  while (v[en] == v[en + 1]) en++;

  if (st > en) st = en = 1;
  reverse(v.begin() + st, v.begin() + en + 1);

  if (is_sorted(v.begin(), v.end())) {
    cout << st << " " << en << "\n";
  }
  else {
    cout << "impossible\n";
  }

  return 0;
}