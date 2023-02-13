#include <bits/stdc++.h>
using namespace std;

void test_case() {
  long long s, n, k;
  cin >> s >> n >> k;
  s++, n++;
  long long mx = s / (2 * k) * k + min(k, s % (2 * k));
  cout << (s == k + 1 or mx < n ? "YES" : "NO") << "\n";
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