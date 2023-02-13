#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n, k;
char c[N];
bool next_is_bigger[N];
int l[N], r[N];
string ans;

char last_c;
bool last_res;
void dfs1(int at) {
  if (at == 0) return;
  dfs1(r[at]);
  next_is_bigger[at] = c[at] < last_c or (c[at] == last_c and last_res);
  last_c = c[at];
  last_res = next_is_bigger[at];
  dfs1(l[at]);
}

bool dfs2(int at, int left_parents, bool right_parents_duped) {
  if (at == 0) return false;

  bool res_l = dfs2(l[at], left_parents + 1, right_parents_duped);

  bool res_at = res_l or (right_parents_duped and next_is_bigger[at] and k >= left_parents + 1);
  k -= res_at;
  ans += c[at];
  if (res_at) ans += c[at];

  dfs2(r[at], left_parents, res_at);

  return res_at;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> k;
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> l[i] >> r[i];
  }

  dfs1(1);
  dfs2(1, 0, true);

  cout << ans << "\n";

  return 0;
}