#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (n == 1) {
    cout << "NO\n";
    return;
  }

  int cnt1 = count(a.begin(), a.end(), 1);
  long long sum = 0;
  for (int i : a) {
    sum += i - 1;
  }

  if (sum < cnt1) cout << "NO\n";
  else cout << "YES\n";
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