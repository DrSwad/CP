#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;

int n, a[N], tree[N << 1];

void update(int p, int v) {
  for (tree[p += n] = v; p > 1; p >>= 1) {
    tree[p >> 1] = max(tree[p], tree[p ^ 1]);
  }
}

int query(int l, int r) {
  int ret = -1;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = max(ret, tree[l++]);
    if (r & 1) ret = max(ret, tree[--r]);
  }
  return ret;
}

int main() {
  memset(tree, -1, sizeof tree);

  int q;
  scanf("%d %d", &n, &q);

  while (q--) {
    int type;
    scanf("%d", &type);

    if (type == 1) {
      int l, r, w;
      scanf("%d %d %d", &l, &r, &w);
      l--, r--;
      if (a[l] < r) {
        a[l] = r;
        update(l, r);
      }
    } else {
      int k;
      scanf("%d", &k);

      vector<int> v(k);
      for (int &i : v) {
        scanf("%d", &i);
        i--;
      }

      int ans = 0;
      for (int i = 0; i < k; ) {
        int res = query(0, v[i] + 1);
        if (res < v[i]) {
          ans = -1;
          break;
        } else {
          i = upper_bound(v.begin(), v.end(), res) - v.begin();
          ans++;
        }
      }

      printf("%d\n", ans);
    }
  }

  return 0;
}