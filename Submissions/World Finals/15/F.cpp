#include <bits/stdc++.h>
using namespace std;

const int N = 55;
const int INF = 1e9;

// down, up, right, left
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int rows, cols;
int tot;
char grid[N * N];
vector<int> char_pos[100];

bool valid(int pos, int dir) {
  int new_pos = pos + dx[dir] + dy[dir];
  if (dir == 2 and new_pos % cols == 0) return false;
  if (dir == 3 and pos % cols == 0) return false;
  return 0 <= new_pos and new_pos < tot;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> rows >> cols;
  tot = rows * cols;

  dx[0] = cols;
  dx[1] = -cols;

  for (int row = 0, at = 0; row < rows; row++) {
    for (int col = 0; col < cols; col++, at++) {
      cin >> grid[at];
      char_pos[grid[at]].push_back(at);
    }
  }

  string text;
  cin >> text;
  text += '*';
  int text_len = text.length();

  vector<int> dp(tot, 0);
  vector<int> sorted(tot);
  iota(sorted.begin(), sorted.end(), 0);

  for (int ti = text_len - 1; ti >= 0; ti--) {
    vector<int> nsorted;
    vector<int> ndp(tot, INF);

    vector<int> cur_char_sorted;
    for (int pos : sorted) {
      if (grid[pos] == text[ti]) {
        ndp[pos] = min(INF, dp[pos] + 1);
        cur_char_sorted.push_back(pos);
      }
    }

    queue<int> q;
    int cur_char_i = 0;

    while (!q.empty() or cur_char_i < cur_char_sorted.size()) {
      int pos;
      if (!q.empty()) {
        if (cur_char_i < cur_char_sorted.size() and ndp[q.front()] >= ndp[cur_char_sorted[cur_char_i]]) {
          pos = cur_char_sorted[cur_char_i++];
        }
        else {
          pos = q.front(), q.pop();
        }
      }
      else pos = cur_char_sorted[cur_char_i++];
      nsorted.push_back(pos);

      int dist = ndp[pos];

      for (int dir = 0; dir < 4; dir++) {
        if (!valid(pos, dir)) continue;

        int nxt_pos = pos + dx[dir] + dy[dir];
        char ch = grid[nxt_pos];
        if (ch == grid[pos]) continue;

        int cur_pos = pos;
        while (valid(cur_pos, dir)) {
          cur_pos = cur_pos + dx[dir] + dy[dir];
          if (grid[cur_pos] != grid[nxt_pos]) break;
          if (ndp[cur_pos] > dist + 1) {
            ndp[cur_pos] = dist + 1;
            q.push(cur_pos);
          }
        }
      }
    }

    swap(dp, ndp);
    swap(sorted, nsorted);
  }

  cout << dp[0] << "\n";

  return 0;
}