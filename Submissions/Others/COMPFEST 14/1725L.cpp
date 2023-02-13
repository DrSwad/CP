#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  multiset<pair<int, int>> ms;
  long long sum = 0;
  for (int i = 0; i < n; i++) {
    sum += a[i];
    if (a[i] < 0) ms.insert({a[i], i});
  }

  if (sum < 0) {
    cout << "-1\n";
    return 0;
  }

  int ans = 0;
  while (!ms.empty()) {
    auto [_, i] = *ms.rbegin();
    a[i - 1]
    a[i] = -a[i];
  }

  return 0;
}