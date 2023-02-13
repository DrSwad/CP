#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (count(a.begin(), a.end(), a[0]) == n) {
    cout << "Yes\n";
    return;
  }

  for (int &i : a) if (i % 10 == 5) i += 5;

  if (count(a.begin(), a.end(), a[0]) == n) {
    cout << "Yes\n";
    return;
  }

  for (int i : a) {
    if (i % 10 == 0) {
      cout << "No\n";
      return;
    }
  }

  for (int &i : a) if (i % 2 == 1) i += i % 10;

  int cnt[2] = {0};
  for (int i : a) {
    int j = i % 20;
    cnt[(j & (j - 1)) == 0]++;
  }

  if (cnt[0] and cnt[1]) cout << "No\n";
  else cout << "Yes\n";
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