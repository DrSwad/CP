#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n, q;
    scanf("%d %d", &n, &q);

    vector<int> a(n);
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
      string str;
      cin >> str;
      scanf("%d", &s[i]);
      int mask = 0;
      for (int i = 0; i < q; i++) {
        if (str[i] == 'T') {
          mask |= 1 << i;
        }
      }
      a[i] = mask;
    }

    int len[2] = {(q + 1) / 2, q / 2};
    map<vector<int>, int> mp[2];
    for (int it = 0; it < 2; it++) {
      if (len[it] == 0) {
        mp[it][vector<int>(n, 0)] = 1;
        continue;
      }

      for (int mask = 0; mask < 1 << len[it]; mask++) {
        vector<int> _s(n, 0);
        bool flag = true;
        for (int i = 0; i < n; i++) {
          for (int j = 0; j < len[it]; j++) {
            if ((a[i] >> (j + (it == 0 ? 0 : len[0])) & 1) == (mask >> j & 1)) {
              _s[i]++;
            }
          }
          if (_s[i] > s[i]) {
            flag = false;
          }
        }
        if (flag) {
          mp[it][_s]++;
        }
      }
    }

    vector<vector<int>> freq(2);
    for (int it = 0; it < 2; it++) {
      freq[it].resize(1 << len[it], 0);
      if (len[it]) {
        for (int mask = 0; mask < 1 << len[it]; mask++) {
          vector<int> _s(n, 0);
          bool flag = true;
          for (int i = 0; i < n; i++) {
            for (int j = 0; j < len[it]; j++) {
              if ((a[i] >> (j + (it == 0 ? 0 : len[0])) & 1) == (mask >> j & 1)) {
                _s[i]++;
              }
            }
            if (_s[i] > s[i]) {
              flag = false;
            } else {
              _s[i] = s[i] - _s[i];
            }
          }
          if (flag) {
            if (mp[it ^ 1].find(_s) != mp[it ^ 1].end()) {
              freq[it][mask] += mp[it ^ 1][_s];
            }
          }
        }
      }
    }

    string ans;
    long long totScore = 0;
    long long totPoss = 0;
    for (int it = 0; it < 2; it++) {
      for (int i = 0; i < len[it]; i++) {
        int cnt[2] = {0};
        for (int mask = 0; mask < 1 << len[it]; mask++) {
          cnt[mask >> i & 1] += freq[it][mask];
          if (it == 0) {
            totPoss += freq[it][mask];
          }
        }
        if (cnt[0] >= cnt[1]) {
          ans += 'F';
          totScore += cnt[0];
        } else {
          ans += 'T';
          totScore += cnt[1];
        }
      }
    }

    long long g = gcd(totScore, totPoss);
    totScore /= g;
    totPoss /= g;

    printf("Case #%d: ", cs);
    cout << ans << " ";
    printf("%d/%d\n", totScore, totPoss);
  }

  return 0;
}