#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n % 2 == 1) puts("Mike");
  else {
    vector<long long> sum(2, 0);
    for (int i = 0; i < n; i++) {
      sum[i & 1] += a[i];
    }

    if (sum[0] > sum[1]) puts("Mike");
    else puts("Joe");
  }
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