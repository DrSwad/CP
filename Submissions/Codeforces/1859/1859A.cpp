#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  vector<int> b, c;
  for (int i : a) {
    if (i == a[0]) b.push_back(i);
    else c.push_back(i);
  }

  if (c.empty()) cout << "-1\n";
  else {
    cout << b.size() << " " << c.size() << "\n";
    for (int i = 0; i < b.size(); i++) {
      if (i) cout << " ";
      cout << b[i];
    }
    cout << "\n";
    for (int i = 0; i < c.size(); i++) {
      if (i) cout << " ";
      cout << c[i];
    }
    cout << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}