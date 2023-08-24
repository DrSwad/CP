#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  map<int, int> mp;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      mp[a[i] + a[j]]++;
    }
  }

  int got = mp.rbegin()->second;
  int tot = n * (n - 1) / 2;

  cout << (double)got / tot << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cout << fixed << setprecision(10);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}