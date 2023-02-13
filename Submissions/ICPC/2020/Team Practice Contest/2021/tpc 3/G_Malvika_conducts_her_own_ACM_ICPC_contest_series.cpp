#include <bits/stdc++.h>
using namespace std;

inline bool tryMove(int &e, int &m, int &h, int &last, int id) {
  if (id == 1 and e and m and h) {
    e--, m--, h--;
    last = 1;
    return true;
  }
  if (id == 2 and m >= 2 and e) {
    m -= 2, e--;
    last = 2;
    return true;
  }
  if (id == 3 and e >= 2 and m) {
    e -= 2, m--;
    last = 3;
    return true;
  }
  return false;
}

inline bool choose(int &e, int &m, int &h, int &last) {
  if (last != 1 and tryMove(e, m, h, last, 1)) return true;
  if (e <= m and last != 2 and tryMove(e, m, h, last, 2)) return true;
  if (m <= e and last != 3 and tryMove(e, m, h, last, 3)) return true;
  if (last != 2 and tryMove(e, m, h, last, 2)) return true;
  if (last != 3 and tryMove(e, m, h, last, 3)) return true;

  return false;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int e, m, h;
    scanf("%d %d %d", &e, &m, &h);

    int cnt[3] = {0};
    for (int i = 0; i < 3; i++) {
      int last = i + 1;
      int E = e, M = m, H = h;
      while (choose(E, M, H, last)) cnt[i]++;
    }

    printf("%d\n", max(cnt[0], max(cnt[1], cnt[2])));
  }

  return 0;
}