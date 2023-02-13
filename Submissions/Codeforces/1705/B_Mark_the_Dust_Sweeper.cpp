#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  bool flag = false;
  int cnt = 0;
  long long sum = 0;

  for (int i = 0; i < n - 1; i++) {
    if (a[i] > 0) flag = true;
    if (flag) cnt += a[i] == 0;
    sum += a[i];
  }

  cout << (sum + cnt) << "\n";
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