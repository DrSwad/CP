#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> freq(101, 0);
  int cnt1 = 0;

  for (int i = 0; i < n; i++) {
    int a;
    cin >> a;
    if (freq[a] & 1) cnt1--;
    freq[a]++;
    if (freq[a] & 1) cnt1++;
  }

  cout << (cnt1 ? "NO\n" : "YES\n");
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