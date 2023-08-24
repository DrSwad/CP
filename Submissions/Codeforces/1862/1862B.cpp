#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> b(n);
  for (int &i : b) cin >> i;

  vector<int> a;
  a.push_back(b[0]);

  for (int i = 1; i < n; i++) {
    if (b[i] >= b[i - 1]) a.push_back(b[i]);
    else a.push_back(1), a.push_back(b[i]);
  }

  cout << a.size() << "\n";
  for (int i = 0; i < a.size(); i++) {
    if (i) cout << " ";
    cout << a[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}