#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = 0;
  vector<int> rems;
  for (int i : a) {
    ans += i / k;
    rems.push_back(i % k);
  }

  sort(rems.begin(), rems.end());

  for (int i = 0, j = rems.size() - 1; i < j; i++, j--) {
    while (i < j and rems[i] + rems[j] < k) i++;
    if (i < j) ans++;
  }

  cout << ans << "\n";
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