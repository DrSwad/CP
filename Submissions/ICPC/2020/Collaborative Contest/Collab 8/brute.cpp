#include <bits/stdc++.h>
using namespace std;

int solve(vector<int> a) {
  if (a.size() <= 1) return 0;

  int ret = INT_MIN;

  for (int i = 0; i < a.size() - 1; i++) {
    vector<int> a0 = a;
    a0.erase(a0.begin() + i);
    a0.erase(a0.begin() + i);
    a0.insert(a0.begin() + i, a[i] * a[i + 1]);

    ret = max(ret, solve(a0) + (a[i] == a[i + 1]) * 2 - 1);
  }

  return ret;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> a(n);
    for (int &i : a) scanf("%d", &i);

    printf("%d\n", solve(a));
  }

  return 0;
}