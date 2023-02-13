#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int A = 32;

int n;
int a[N];
vector<int> children[N];
vector<int> dp[N][A];
int sz[N];

void dp_dfs(int at) {
  DB();
  debug(at + 1);
  vector<vector<int>> ndp(A);

  ndp[0].push_back(0);
  for (int x = 1; x < A; x++) {
    ndp[x].push_back(-1);
  }

  sz[at] = 1;

  for (int i = 0; i < children[at].size(); i++) {
    int ch = children[at][i];
    dp_dfs(ch);
    sz[at] += sz[ch];

    for (int px = 0; px < A; px++) {
      if (ndp[px][i] == -1) continue;
      for (int cx = 0; cx < A; cx++) {
        if (dp[ch][cx].back() == -1) continue;
        int x = px ^ cx;
        if (ndp[x].size() <= i + 1) ndp[x].push_back(cx);
      }
    }

    for (int x = 0; x < A; x++) {
      if (ndp[x].size() <= i + 1) ndp[x].push_back(-1);
    }
  }

  for (int x = 0; x < A; x++) {
    for (int i = 0; i <= children[at].size(); i++) {
      int y = i < children[at].size() ? x : x ^ a[at];
      dp[at][y].push_back(ndp[x][i]);
    }
  }

  if (sz[at] % 2 == 0) dp[at][0].back() = A;
  // for (int x = 0; x < A; x++) debug(x, ndp[x]);
}

vector<int> ans;

void generate_ans(int at, int x) {
  debug(at, x);
  if (x == 0 and sz[at] % 2 == 0) {
    ans.push_back(at);
    return;
  }

  for (int i = children[at].size(); i > 0; i--) {
    int y = dp[at][x][i];
    generate_ans(children[at][i - 1], y);
    x ^= y;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }

  for (int i = 1; i <= n - 1; i++) {
    int p;
    cin >> p;
    p--;
    children[p].push_back(i);
  }

  dp_dfs(0);
  if (dp[0][0].back() == -1) cout << "-1\n";
  else {
    generate_ans(0, 0);
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
      if (i) cout << " ";
      cout << ans[i] + 1;
    }
    cout << "\n";
  }

  return 0;
}