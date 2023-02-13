#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int d, n, k;
  cin >> d >> n >> k;

  for (int i = 0; i < d; i++) {
    cin >> h[i];

    int s, e;
    cin >> s >> e;
    upd[s].push_back(i);
    upd[e + 1].push_back(-i);
  }

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