#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> p(n);
  for (int &i : p) cin >> i, i--;

  long long ans = 0;
  for (int bi = 1; bi < n - 2; bi++) {
    vector<bool> avis(n, false);
    for (int i = 0; i < bi; i++) {
      avis[p[i]] = true;
    }

    vector<int> ccnt(n);
    ccnt[0] = avis[0];
    for (int a = 1; a < n; a++) {
      ccnt[a] += ccnt[a - 1] + avis[a];
    }

    int tot_ccnt = 0;
    for (int di = bi + 1; di < n; di++) {
      if (p[di] < p[bi]) {
        ans += tot_ccnt;
      }

      tot_ccnt += ccnt[p[di]];
    }
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