#include <bits/stdc++.h>
using namespace std;

int n, m, s;
int take;
vector<int> mv;

bool check(int mi, int ni) {
  int st = ni;
  int en = st + take - 1;

  int ei = upper_bound(mv.begin(), mv.end(), en) - mv.begin();
  int need = take - (ei - mi);

  return need <= s;
}

int main() {
  scanf("%d %d %d", &n, &m, &s);
  take = m;

  mv.resize(m);
  for (int &i : mv) scanf("%d", &i);
  sort(mv.begin(), mv.end());
  mv.resize(unique(mv.begin(), mv.end()) - mv.begin());

  m = mv.size();
  int ans = 0;

  for (int mi = 0; mi < m; mi++) {
    int st = mi == 0 ? 1 : (mv[mi - 1] + 1);
    int en = mv[mi];

    int L = st, R = en;
    while (L != R) {
      int mid = (L + R) / 2;
      if (check(mi, mid)) R = mid;
      else L = mid + 1;
    }

    if (check(mi, L)) {
      ans += max(0, min(en, n - (take - 1)) - (L - 1));
    }
  }

  printf("%d\n", ans);

  return 0;
}