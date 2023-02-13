#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 1e5 + 5;
const int LOGN = 17;

int n;
int d[N][2][2];
ll jump[LOGN][N][2][2];

ll same_layer_dist(int x1, int y1, int x2, int y2) {
  int l1 = max(x1, y1);
  int l2 = max(x2, y2);
  assert(l1 == l2);

  if (l1 == x1 and l2 == x2) return abs(y1 - y2);
  else if (l1 == y1 and l2 == y2) return abs(x1 - x2);
  else return (l1 - min(x1, y1)) + (l2 - min(x2, y2));
}

void init_layer_dist() {
  for (int l = 1; l < n - 1; l++) {
    for (int d1 = 0; d1 < 2; d1++) {
      for (int d2 = 0; d2 < 2; d2++) {
        int x1 = d[l][d1][0];
        int y1 = d[l][d1][1];
        int x2 = d[l + 1][d2][0];
        int y2 = d[l + 1][d2][1];

        jump[0][l][d1][d2] = 1;

        if (d1 == 0) x1++;
        else y1++;

        jump[0][l][d1][d2] += same_layer_dist(x1, y1, x2, y2);
      }
    }
  }

  for (int j = 1; j < LOGN; j++) {
    for (int l = 1; l < n - 1; l++) {
      if (l + (1 << j) >= n) continue;
      for (int d1 = 0; d1 < 2; d1++) {
        for (int d2 = 0; d2 < 2; d2++) {
          for (int dm = 0; dm < 2; dm++) {
            ll moves1 = jump[j - 1][l][d1][dm];
            ll moves2 = jump[j - 1][l + (1 << (j - 1))][dm][d2];
            if (moves1 and moves2) {
              ll &ans = jump[j][l][d1][d2];
              ll curr = moves1 + moves2;
              ans = ans == 0 ? curr : min(ans, curr);
            }
          }
        }
      }
    }
  }
}

ll layer_dist(int l1, int d1, int l2, int d2) {
  if (l1 == l2) {
    return same_layer_dist(d[l1][d1][0], d[l1][d1][1], d[l2][d2][0], d[l2][d2][1]);
  }

  if (l1 > l2) swap(l1, l2), swap(d1, d2);
  int ldiff = l2 - l1;

  int from = l2;
  vector<ll> cdist(2, 0);
  for (int j = LOGN - 1; j >= 0; j--) {
    if (ldiff >> j & 1) {
      int to = from - (1 << j);
      vector<ll> ndist(2, LLONG_MAX);

      for (int fd = 0; fd < 2; fd++) {
        for (int td = 0; td < 2; td++) {
          if (from != l2 or fd == d2) {
            ndist[td] = min(ndist[td], cdist[fd] + jump[j][to][td][fd]);
          }
        }
      }

      swap(cdist, ndist);
      from = to;
    }
  }

  return cdist[d1];
}

ll dist(int x1, int y1, int x2, int y2) {
  int l1 = max(x1, y1);
  int l2 = max(x2, y2);
  if (l1 == l2) return same_layer_dist(x1, y1, x2, y2);

  if (l1 > l2) swap(l1, l2), swap(x1, x2), swap(y1, y2);

  ll ans = LLONG_MAX;
  for (int d1 = 0; d1 < 2; d1++) {
    for (int d2 = 0; d2 < 2; d2++) {
      ll curr = 0;
      curr += same_layer_dist(x1, y1, d[l1][d1][0], d[l1][d1][1]);
      curr += layer_dist(l1, d1, l2 - 1, d2);
      int x3 = d[l2 - 1][d2][0] + (d2 == 0);
      int y3 = d[l2 - 1][d2][1] + (d2 == 1);
      curr++;
      curr += same_layer_dist(x2, y2, x3, y3);
      ans = min(ans, curr);
    }
  }

  return ans;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i < n; i++) {
    cin >> d[i][0][0] >> d[i][0][1] >> d[i][1][0] >> d[i][1][1];
  }

  init_layer_dist();

  int m;
  cin >> m;

  while (m--) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    cout << dist(x1, y1, x2, y2) << "\n";
  }

  return 0;
}