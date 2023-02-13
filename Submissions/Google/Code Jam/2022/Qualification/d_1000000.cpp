#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  int at, i;
  for (at = 1, i = 0; ; at++, i++) {
    while (i < n and a[i] < at) i++;
    if (i == n) break;
  }

  cout << at - 1 << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}