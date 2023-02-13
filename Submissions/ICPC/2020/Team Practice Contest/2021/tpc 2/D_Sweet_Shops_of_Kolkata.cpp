#include <bits/stdc++.h>
using namespace std;

pair<int, vector<int>> solve(int n, int pos, int val) {
  if (n == 1) return {0, {val}};
  pos--;

  vector<int> v(n);
  iota(v.begin(), v.end(), 1);
  if (v[pos] == val) return {1, v};
  reverse(v.begin(), v.end());
  if (v[pos] == val) return {1, v};

  for (int i = 0; i < (n + 1) / 2; i++) v[i] = 2 * i + 1;
  for (int i = (n + 1) / 2, j = n / 2; i < n; i++, j--) v[i] = 2 * j;

  int pos_diff = (find(v.begin(), v.end(), val) - v.begin() - pos + n) % n;
  rotate(v.begin(), v.begin() + pos_diff, v.end());

  return {2, v};
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, pos, val;
    scanf("%d %d %d", &n, &pos, &val);

    auto got = solve(n, pos, val);
    int diff = got.first;
    auto ans = got.second;

    printf("%d\n", diff);
    for (int i = 0; i < ans.size(); i++) {
      if (i) printf(" ");
      printf("%d", ans[i]);
    }
    puts("");
  }

  return 0;
}