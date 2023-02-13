#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx = *max_element(a.begin(), a.end());
  a.insert(a.begin(), mx);
  a.push_back(mx);

  for (int i = 1; i <= n; i++) {
    if (a[i] == mx and a[i - 1] != mx) {
      cout << i << "\n";
      return;
    }
    if (a[i] == mx and a[i + 1] != mx) {
      cout << i << "\n";
      return;
    }
  }

  cout << "-1\n";
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