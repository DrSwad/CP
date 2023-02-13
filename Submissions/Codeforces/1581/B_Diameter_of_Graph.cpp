#include <bits/stdc++.h>
using namespace std;

void answer(bool ans) {
  cout << (ans ? "YES" : "NO") << "\n";
}

void test_case() {
  int n, m, k;
  cin >> n >> m >> k;

  if (m < n - 1) return answer(false);
  long long mx = (long long)n * (n - 1) / 2;
  if (m > mx) return answer(false);
  if (k - 2 >= 2) return answer(true);
  if (m == mx and k - 2 >= 1) return answer(true);
  if (n == 1 and k - 2 >= 0) return answer(true);
  return answer(false);
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