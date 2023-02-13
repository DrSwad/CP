#include <bits/stdc++.h>
using namespace std;

int main() {
  int n, k;
  scanf("%d %d", &n, &k);

  vector<pair<int, int>> ball;
  vector<int> final_pos;

  for (int i = 0; i < n; i++) {
    int p, v;
    scanf("%d %d", &p, &v);
    ball.emplace_back(p, v);
    final_pos.push_back(p + k * v);
  }

  sort(final_pos.begin(), final_pos.end());

  vector<int> order(n);
  iota(order.begin(), order.end(), 0);
  sort(order.begin(), order.end(), [&](int i, int j) {
    return ball[i].first < ball[j].first;
  });

  vector<int> ans(n);
  for (int i = 0; i < n; i++) {
    ans[order[i]] = final_pos[i];
  }

  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", ans[i]);
  }
  puts("");

  return 0;
}