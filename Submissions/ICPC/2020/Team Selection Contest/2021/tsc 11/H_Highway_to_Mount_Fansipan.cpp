#include <bits/stdc++.h>
using namespace std;

const int MOD = 1e9 + 7;
const int A = 26;
const int W = 51;

int main() {
  int t;
  cin >> t;

  vector<int> freq(A * W, 0);

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> w(n);
    for (int i = 0; i < n; i++) scanf("%d", &w[i]);

    int dSz;
    scanf("%d", &dSz);

    vector<string> d(dSz);
    for (int i = 0; i < dSz; i++) cin >> d[i];

    for (int i = 0; i < dSz; i++) {
      int curr = (d[i][0] - 'a') * W + d[i].size();
      freq[curr]++;
    }

    long long ans = 0;
    for (int i = 0; i < dSz; i++) {
      if (d[i].size() != n) continue;

      int curr = (d[i][0] - 'a') * W + d[i].size();
      freq[curr]--;

      long long currAns = 1;
      for (int j = 0; j < n; j++) {
        int need = (d[i][j] - 'a') * W + w[j];
        (currAns *= freq[need]) %= MOD;
        freq[need]--;
      }
      (ans += currAns) %= MOD;

      for (int j = 0; j < n; j++) {
        int need = (d[i][j] - 'a') * W + w[j];
        freq[need]++;
      }

      freq[curr]++;
    }

    printf("%lld\n", ans);

    for (int i = 0; i < dSz; i++) {
      int curr = (d[i][0] - 'a') * W + d[i].size();
      freq[curr]--;
    }
  }

  return 0;
}
