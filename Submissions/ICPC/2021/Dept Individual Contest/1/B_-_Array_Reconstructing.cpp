#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int st;
  for (st = 0; st < n; st++) {
    if (a[st] != -1) break;
  }

  for (int i = st - 1; i >= 0; i--) {
    a[i] = (a[i + 1] + m - 1) % m;
  }
  for (int i = st + 1; i < n; i++) {
    a[i] = (a[i - 1] + 1) % m;
  }

  for (int i = 0; i < n; i++) {
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