#include <bits/stdc++.h>
using namespace std;

void test_case() {
  string P, Q, X;
  cin >> P >> Q >> X;

  long long ans = 0;

  for (int p = 0; p <= P.size(); p++) {
    for (int q = 0; q <= Q.size(); q++) {
      string pq = P.substr(0, p) + Q.substr(0, q);
      for (int x = 0; x < X.size(); x++) {
        if (X.substr(x, pq.length()) == pq) {
          ans++;
          break;
        }
      }
    }
  }

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