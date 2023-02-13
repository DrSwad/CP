#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, H;
  cin >> n >> H;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  int A = a.back();
  a.pop_back();
  int B = a.back();

  int ans = H / (A + B) * 2;
  H %= (A + B);
  ans += H > 0;
  H = max(0, H - A);
  ans += H > 0;

  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}