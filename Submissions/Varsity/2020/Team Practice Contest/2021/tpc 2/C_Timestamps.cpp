#include <bits/stdc++.h>
using namespace std;

vector<int> times[4][11][7][11][7][11];

int main() {
  vector<int> d(6);

  for (int h = 0; h < 24; h++) {
    d[0] = h / 10;
    d[1] = h % 10;
    d[0]++;
    d[1]++;

    for (int m = 0; m < 60; m++) {
      d[2] = m / 10;
      d[3] = m % 10;
      d[2]++;
      d[3]++;

      for (int s = 0; s < 60; s++) {
        d[4] = s / 10;
        d[5] = s % 10;
        d[4]++;
        d[5]++;

        int curr_time = h * 60 * 60 + m * 60 + s;

        for (int mask = 0; mask < 1 << 6; mask++) {
          vector<int> t(6, 0);
          for (int i = 0; i < 6; i++) {
            if (mask >> i & 1) {
              t[i] = d[i];
            }
          }
          times[t[0]][t[1]][t[2]][t[3]][t[4]][t[5]].push_back(curr_time);
        }
      }
    }
  }

  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    int days = 0, seconds = 0;
    char s[10];

    while (n--) {
      scanf("%s", s);

      vector<int> t(6, 0);
      for (int i = 0, d = 0; i < 8; i++) {
        if (s[i] != ':') {
          if (s[i] != '?') t[d] = s[i] - '0' + 1;
          d++;
        }
      }
      vector<int> &T = times[t[0]][t[1]][t[2]][t[3]][t[4]][t[5]];

      auto it = lower_bound(T.begin(), T.end(), seconds);
      if (it != T.end()) {
        seconds = *it;
      } else {
        days++;
        seconds = T[0];
      }
    }

    printf("%lld\n", days * 1ll * 24 * 60 * 60 + seconds);
  }

  return 0;
}