#include <bits/stdc++.h>
using namespace std;

bool check(int n, vector<int> a, int at) {
  while (n > 1) {
    if (at != 0 and a[at - 1] <= a[at]) {
      a[at]++;
      a.erase(a.begin() + (at - 1));
      at--;
    } else if (at != n - 1 and a[at + 1] <= a[at]) {
      a[at]++;
      a.erase(a.begin() + (at + 1));
    } else return false;
    n--;
  }
  return true;
}

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int &i : a) scanf("%d", &i);

    vector<int> ans(n, 0);
    vector<int> b(n);
    iota(b.begin(), b.end(), 0);
    do {
      vector<int> _a;
      for (int i : b) _a.emplace_back(a[i]);
      for (int i = 0; i < n; i++) {
        ans[b[i]] += check(n, _a, i);
      }
    } while (next_permutation(b.begin(), b.end()));

    printf("Case %d:\n", cs);
    for (int i : ans) printf("%d\n", i);
  }

  return 0;
}