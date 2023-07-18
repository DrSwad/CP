#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, m, h;
  cin >> n >> m >> h;

  vector<tuple<int, long long, int>> standings;
  for (int row = 0; row < n; row++) {
    vector<int> t(m);
    for (int &i : t) cin >> i;

    sort(t.begin(), t.end());

    int points = 0;
    long long penalty = 0;
    int time_spent = 0;

    for (int i : t) {
      time_spent += i;
      if (time_spent <= h) {
        points++;
        penalty += time_spent;
      }
    }

    standings.emplace_back(-points, penalty, row + 1);
  }

  sort(standings.begin(), standings.end());

  for (int i = 0; i < n; i++) {
    if (get<2>(standings[i]) == 1) {
      cout << i + 1 << "\n";
      return;
    }
  }

  assert(false);
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