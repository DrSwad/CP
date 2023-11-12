#include <bits/stdc++.h>
using namespace std;

const int max_rooms = 305;

void test_case() {
  int traps;
  cin >> traps;

  vector<int> vs(max_rooms + 1, 2 * max_rooms + 1);
  while (traps--) {
    int d, s;
    cin >> d >> s;
    vs[d] = min(vs[d], s - 1);
  }

  int ans = max_rooms;
  for (int at = 1; at <= ans; at++) {
    ans = min(ans, at + vs[at] / 2);
  }

  cout << ans << "\n";
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