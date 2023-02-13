#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p;
  if (n % 2 == 0) {
    for (int i = n - 2; i >= 1; i--) {
      p.push_back(i);
    }
    p.push_back(n - 1);
    p.push_back(n);
  }
  else {
    p.push_back(1);
    p.push_back(2);
    p.push_back(3);
    for (int i = n - 2; i >= 4; i--) {
      p.push_back(i);
    }
    p.push_back(n - 1);
    p.push_back(n);
  }

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << p[i];
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