#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;
int n, a[N], tree[N << 1];

void init() {
  for (int i = 0; i < n; ++i) { tree[n + i] = a[i]; }
  for (int i = n - 1; i >= 0; --i) {
    tree[i] = max(tree[i << 1], tree[i << 1 | 1]);
  }
}

int query(int l, int r) {
  int ret = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l & 1) ret = max(ret, tree[l++]);
    if (r & 1) ret = max(ret, tree[--r]);
  }
  return ret;
}

int main() {
  scanf("%d", &n);

  map<int, bool> bad;

  for (int it = 0; it < 2; it++) {
    map<int, int> lastFound;
    vector<tuple<int, int, int>> weights;

    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);

      if (lastFound.find(a[i]) != lastFound.end()) {
        weights.emplace_back(a[i], lastFound[a[i]], i);
        lastFound.erase(a[i]);
      }
      else {
        lastFound[a[i]] = i;
      }
    }

    for (auto [w, at] : lastFound) {
      bad[w] = true;
    }

    init();

    for (auto [w, st, en] : weights) {
      if (en != st + 1) {
        int mw = query(st + 1, en);
        bad[mw < w ? mw : w] = true;
      }
    }
  }

  int ans = !bad.empty() ? bad.rbegin()->first : 0;
  cout << ans << endl;

  return 0;
}