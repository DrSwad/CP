#include <bits/stdc++.h>

using namespace std;

const int N = 1e3 + 5;
int max_val[N][N];
int min_val[N][N];

vector<int> pos[N];

int solve(int L, int R) {
  if (L > R) return 0;
  min_val[L][R]

}

int main() {

  int n;
  cin >> n;

  vector<int> L(n);
  vector<char> c(n);

  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      min_val[i][j] = inf;
    }
  }

  for (int i = 0; i < n; i++) {
    cin >> c[i] >> L[i];

    if (c[i] == 'n') {
      pos[L[i]].push_back(i);
      max_val[i][i] = L[i];
    } else {
      min_val[i][i] = L[i];
    }
  }

  for (int i = 1; i <= n; i++) {
    for (int j = i + 1; j <= n; j++) {
      if (c[i] == 'y')
        else max_val[i][j] = max(max_val[i][j - 1], max_val[i][j]);
    }
  }

  return 0;
}