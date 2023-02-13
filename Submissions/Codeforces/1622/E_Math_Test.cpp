#include <bits/stdc++.h>
using namespace std;

const int N = 12;
const int M = 1e4 + 5;

int n, m;
int x[N];
bool g[N][M];

int f[M];
long long curr_surprise, max_surprise;
int ans[M];

void go(int at) {
  if (at == n) {
    vector<int> points_at_problem(m);
    iota(points_at_problem.begin(), points_at_problem.end(), 0);
    sort(
      points_at_problem.begin(),
      points_at_problem.end(),
      [&](int i, int j) {
      return f[i] < f[j];
    }
      );

    long long prev_surprise = curr_surprise;
    for (int p = 0; p < m; p++) {
      curr_surprise += (long long)(p + 1) * f[points_at_problem[p]];
    }

    if (curr_surprise > max_surprise) {
      max_surprise = curr_surprise;
      for (int p = 0; p < m; p++) {
        ans[points_at_problem[p]] = p + 1;
      }
    }
    curr_surprise = prev_surprise;
    return;
  }

  long long prev_surprise = curr_surprise;
  curr_surprise += x[at];
  for (int i = 0; i < m; i++) {
    if (g[at][i]) f[i]--;
  }
  go(at + 1);
  for (int i = 0; i < m; i++) {
    if (g[at][i]) f[i]++;
  }

  curr_surprise = prev_surprise;
  prev_surprise = curr_surprise;

  curr_surprise -= x[at];
  for (int i = 0; i < m; i++) {
    if (g[at][i]) f[i]++;
  }
  go(at + 1);
  for (int i = 0; i < m; i++) {
    if (g[at][i]) f[i]--;
  }

  curr_surprise = prev_surprise;
}

void reset() {
  for (int i = 0; i < m; i++) {
    f[i] = 0;
  }
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      g[i][j] = false;
    }
  }
  curr_surprise = 0;
  max_surprise = LLONG_MIN;
}

void test_case() {
  cin >> n >> m;

  for (int i = 0; i < n; i++) {
    cin >> x[i];
  }

  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    for (int j = 0; j < m; j++) {
      g[i][j] = s[j] == '1';
    }
  }

  go(0);

  for (int i = 0; i < m; i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  reset();
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