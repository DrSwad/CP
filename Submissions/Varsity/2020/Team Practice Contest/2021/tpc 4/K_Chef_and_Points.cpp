#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second

const int N = 2005;

int n;
point p[N];
int dp[N][N];
vector<int> v[N];

bool is_smaller_slope(int p1, int p2, int q1, int q2) {
  if (p2 < p1) swap(p1, p2);
  if (q2 < q1) swap(q1, q2);
  return (long long)(p[p2].y - p[p1].y) * (p[q2].x - p[q1].x) < (long long)(p[q2].y - p[q1].y) * (p[p2].x - p[p1].x);
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
      scanf("%d %d", &p[i].x, &p[i].y);
    }

    if (n == 1) {
      puts("1");
      continue;
    }

    sort(p, p + n, [&](const point &p1, const point &p2) {
      return p1.x < p2.x;
    });

    int ans = 0;

    for (int p2 = n - 1; ~p2; p2--) {
      v[p2].clear();
      for (int i = p2 + 1; i < n; i++) v[p2].push_back(i);
      sort(v[p2].begin(), v[p2].end(), [&](int i, int j) {
        return is_smaller_slope(p2, i, p2, j);
      });

      vector<int> best;
      for (int i = 0, prv_best = -1; i < v[p2].size(); i++) {
        prv_best = max(prv_best, dp[v[p2][i]][p2]);
        best.push_back(prv_best);
      }

      for (int p1 = p2 - 1; ~p1; p1--) {
        int up = upper_bound(v[p2].begin(), v[p2].end(), p1, [&](int i, int j) {
          return is_smaller_slope(p2, i, p2, j);
        }) - v[p2].begin();
        dp[p2][p1] = 1 + (up ? best[up - 1] : 1);
        ans = max(ans, dp[p2][p1]);
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}