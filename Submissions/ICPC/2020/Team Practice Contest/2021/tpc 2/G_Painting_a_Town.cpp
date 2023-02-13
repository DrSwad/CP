#include <bits/stdc++.h>
using namespace std;

typedef long double ld;
const int N = 2005;
const int MAX_EXP = 50;

int n, m;
int g[N][N];
int nextEmptyUp[N][N];
int nextEmptyLeft[N][N];
int maxColorUp[N][N][4];
int maxColorLeft[N][N][4];
int maxColorSquare[N][N][4];
int maxSameColorSquare[N][N];

int main() {
  scanf("%d %d", &n, &m);

  vector<int> charIndex(max('R', '*') + 1);
  charIndex['*'] = 0;
  charIndex['R'] = 1;
  charIndex['G'] = 2;
  charIndex['B'] = 3;

  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= m; c++) {
      char ch;
      scanf(" %c", &ch);
      g[r][c] = charIndex[ch];
    }
  }

  for (int r = 1; r <= n; r++) {
    for (int c = 1; c <= m; c++) {
      for (int color = 0; color <= 3; color++) {
        maxColorUp[r][c][color] = g[r][c] and g[r][c] != color ? 0 : 1 + maxColorUp[r - 1][c][color];

        maxColorLeft[r][c][color] = g[r][c] and g[r][c] != color ? 0 : 1 + maxColorLeft[r][c - 1][color];

        maxColorSquare[r][c][color] = g[r][c] and g[r][c] != color ? 0 : min(min(maxColorUp[r][c][color], maxColorLeft[r][c][color]), 1 + maxColorSquare[r - 1][c - 1][color]);

        maxSameColorSquare[r][c] = max(maxSameColorSquare[r][c], maxColorSquare[r][c][color]);
      }

      nextEmptyUp[r][c] = !g[r - 1][c] ? 1 : 1 + nextEmptyUp[r - 1][c];

      nextEmptyLeft[r][c] = !g[r][c - 1] ? 1 : 1 + nextEmptyLeft[r][c - 1];
    }
  }

  vector<ld> inv3(MAX_EXP);
  inv3[0] = 1;
  for (int i = 1; i < MAX_EXP; i++) {
    inv3[i] = inv3[i - 1] / 3;
  }

  ld ans = 0;
  for (int diagonal = -(m - 2); diagonal <= n; diagonal++) {
    int r, c;
    if (diagonal <= 0) {
      r = 1;
      c = 2 - diagonal;
    } else {
      r = diagonal;
      c = 1;
    }

    vector<int> prev_queue, curr_queue;
    for ( ; r <= n and c <= m; r++, c++) {
      if (!g[r][c]) curr_queue.push_back(1);
      for (int dist = 0, diag = 0; ; ) {
        int cnt = 0;
        int new_dist = N;

        if (c - dist > 0 and c - dist - nextEmptyLeft[r][c - dist] > 0) {
          int candidate = nextEmptyLeft[r][c - dist] + dist;
          if (candidate < min(r, c)) {
            if (candidate == new_dist) cnt++;
            else if (candidate < new_dist) cnt = 1;
            new_dist = min(new_dist, candidate);
          }
        }

        if (r - dist > 0 and r - dist - nextEmptyUp[r - dist][c] > 0) {
          int candidate = nextEmptyUp[r - dist][c] + dist;
          if (candidate < min(r, c)) {
            if (candidate == new_dist) cnt++;
            else if (candidate < new_dist) cnt = 1;
            new_dist = min(new_dist, candidate);
          }
        }

        while (diag < prev_queue.size()) {
          int candidate = prev_queue[diag];
          if (candidate == new_dist) cnt++;
          else if (candidate < new_dist) cnt = 1;
          else break;
          new_dist = min(new_dist, candidate);
          diag++;
        }

        if (!cnt) break;
        if (curr_queue.size() + cnt >= MAX_EXP) break;
        while (cnt--) curr_queue.push_back(new_dist + 1);
        dist = new_dist;
      }

      vector<pair<int, int>> goTill{{maxColorSquare[r][c][0], 3}, {maxSameColorSquare[r][c], 1}};
      int at = 0;

      for (int it = 0; it < 2; it++) {
        int max_dim = goTill[it].first;
        int coeff = goTill[it].second;

        int prev_dim = it ? goTill[it - 1].first : 0;
        int new_dim = min(at < curr_queue.size() ? curr_queue[at] - 1 : N, max_dim);
        int empty_freq = at;
        ans += coeff * (new_dim - prev_dim) * inv3[empty_freq];

        while (at < curr_queue.size() and curr_queue[at] <= max_dim) {
          int nxt = at + 1;
          while (nxt < curr_queue.size() and curr_queue[nxt] == curr_queue[at]) nxt++;

          int curr_dim = curr_queue[at];
          int nxt_dim = min((nxt < curr_queue.size() ? curr_queue[nxt] : N), max_dim + 1);
          int empty_freq = nxt;

          ans += coeff * (nxt_dim - curr_dim) * inv3[empty_freq];

          at = nxt;
        }
      }

      swap(prev_queue, curr_queue);
      curr_queue.clear();
    }
  }

  cout << fixed << setprecision(6) << ans << endl;
}