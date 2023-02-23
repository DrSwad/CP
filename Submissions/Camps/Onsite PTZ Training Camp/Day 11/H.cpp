#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;
const int BASE = 2397233;
const int MOD = 1e9 + 7;
int n, a[N], tree_mul[N << 2], tree_add[N << 2];

void add(int &a, int b) {
  int c = a + b;
  a = c >= MOD ? c - MOD : c;
}

void mul(int &a, int b) {
  a = 1ll * a * b % MOD;
}

inline void push(int u, int b, int e) {
  if (b != e) {
    for (int it = 0; it < 2; it++) {
      mul(tree_mul[u << 1 | it], tree_mul[u]);
      mul(tree_add[u << 1 | it], tree_mul[u]);
      add(tree_add[u << 1 | it], tree_add[u]);
    }
    tree_mul[u] = 1;
    tree_add[u] = 0;
  }
}

// add v on range [l, r]
void update(int l, int r, int v, int u = 1, int b = 1, int e = n) {
  // DB();
  // debug(l, r, v, u, b, e);
  // debug(tree_mul[u], tree_add[u]);
  push(u, b, e);
  if (b > r or e < l) return;
  if (b >= l and e <= r) {
    mul(tree_mul[u], BASE);
    mul(tree_add[u], BASE);
    add(tree_add[u], v);
    // debug(tree_mul[u], tree_add[u]);
    return push(u, b, e);
  }
  int mid = b + e >> 1;
  update(l, r, v, u << 1, b, mid), update(l, r, v, u << 1 | 1, mid + 1, e);
}

// value on id
int query(int id, int u = 1, int b = 1, int e = n) {
  // DB();
  // debug(id, u, b, e);
  if (b > id or e < id) return 0;
  // debug(tree_mul[u], tree_add[u]);
  push(u, b, e);
  if (b == e) {
    int ret = tree_add[u];
    // debug(ret);
    return ret;
  }
  int mid = b + e >> 1;
  int ret = max(
    query(id, u << 1, b, mid),
    query(id, u << 1 | 1, mid + 1, e)
    );
  // debug(ret);
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  fill(begin(tree_mul), end(tree_mul), 1);

  int k;
  cin >> n >> k;

  int t;
  cin >> t;

  while (t--) {
    int l, r, x;
    cin >> l >> r >> x;
    // debug(l, r, x);
    update(l, r, x);
  }

  int need = 0;
  for (int x = 1; x <= k; x++) {
    mul(need, BASE);
    add(need, x);
  }
  // debug(need);

  int ans = 0;
  for (int i = 1; i <= n; i++) {
    ans += query(i) == need;
    // debug(i, ans);
  }

  cout << ans << "\n";

  return 0;
}

/* Logs
   [l, r, x]: 2 3 1
   {
   [l, r, v, u, b, e]: 2 3 1 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 2 3 1 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [l, r, v, u, b, e]: 2 3 1 4 1 2
      [tree_mul[u], tree_add[u]]: 1 0
      {
        [l, r, v, u, b, e]: 2 3 1 8 1 1
        [tree_mul[u], tree_add[u]]: 1 0
      }
      {
        [l, r, v, u, b, e]: 2 3 1 9 2 2
        [tree_mul[u], tree_add[u]]: 1 0
        [tree_mul[u], tree_add[u]]: 10 1
      }
    }
    {
      [l, r, v, u, b, e]: 2 3 1 5 3 3
      [tree_mul[u], tree_add[u]]: 1 0
      [tree_mul[u], tree_add[u]]: 10 1
    }
   }
   {
    [l, r, v, u, b, e]: 2 3 1 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
   }
   }
   [l, r, x]: 1 3 2
   {
   [l, r, v, u, b, e]: 1 3 2 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 1 3 2 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    [tree_mul[u], tree_add[u]]: 10 2
   }
   {
    [l, r, v, u, b, e]: 1 3 2 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
   }
   }
   [l, r, x]: 4 5 1
   {
   [l, r, v, u, b, e]: 4 5 1 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 4 5 1 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
   }
   {
    [l, r, v, u, b, e]: 4 5 1 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    [tree_mul[u], tree_add[u]]: 10 1
   }
   }
   [l, r, x]: 2 4 3
   {
   [l, r, v, u, b, e]: 2 4 3 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 2 4 3 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [l, r, v, u, b, e]: 2 4 3 4 1 2
      [tree_mul[u], tree_add[u]]: 10 2
      {
        [l, r, v, u, b, e]: 2 4 3 8 1 1
        [tree_mul[u], tree_add[u]]: 10 2
      }
      {
        [l, r, v, u, b, e]: 2 4 3 9 2 2
        [tree_mul[u], tree_add[u]]: 100 12
        [tree_mul[u], tree_add[u]]: 1000 123
      }
    }
    {
      [l, r, v, u, b, e]: 2 4 3 5 3 3
      [tree_mul[u], tree_add[u]]: 100 12
      [tree_mul[u], tree_add[u]]: 1000 123
    }
   }
   {
    [l, r, v, u, b, e]: 2 4 3 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [l, r, v, u, b, e]: 2 4 3 6 4 4
      [tree_mul[u], tree_add[u]]: 10 1
      [tree_mul[u], tree_add[u]]: 100 13
    }
    {
      [l, r, v, u, b, e]: 2 4 3 7 5 5
      [tree_mul[u], tree_add[u]]: 10 1
    }
   }
   }
   [l, r, x]: 3 5 2
   {
   [l, r, v, u, b, e]: 3 5 2 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 3 5 2 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [l, r, v, u, b, e]: 3 5 2 4 1 2
      [tree_mul[u], tree_add[u]]: 1 0
    }
    {
      [l, r, v, u, b, e]: 3 5 2 5 3 3
      [tree_mul[u], tree_add[u]]: 1000 123
      [tree_mul[u], tree_add[u]]: 10000 1232
    }
   }
   {
    [l, r, v, u, b, e]: 3 5 2 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    [tree_mul[u], tree_add[u]]: 10 2
   }
   }
   [l, r, x]: 5 5 3
   {
   [l, r, v, u, b, e]: 5 5 3 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [l, r, v, u, b, e]: 5 5 3 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
   }
   {
    [l, r, v, u, b, e]: 5 5 3 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [l, r, v, u, b, e]: 5 5 3 6 4 4
      [tree_mul[u], tree_add[u]]: 1000 132
    }
    {
      [l, r, v, u, b, e]: 5 5 3 7 5 5
      [tree_mul[u], tree_add[u]]: 100 12
      [tree_mul[u], tree_add[u]]: 1000 123
    }
   }
   }
   [need]: 321
   {
   [id, u, b, e]: 1 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [id, u, b, e]: 1 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [id, u, b, e]: 1 4 1 2
      [tree_mul[u], tree_add[u]]: 1 0
      {
        [id, u, b, e]: 1 8 1 1
        [tree_mul[u], tree_add[u]]: 10 2
        [ret]: 2
      }
      {
        [id, u, b, e]: 1 9 2 2
      }
      [ret]: 2
    }
    {
      [id, u, b, e]: 1 5 3 3
    }
    [ret]: 2
   }
   {
    [id, u, b, e]: 1 3 4 5
   }
   [ret]: 2
   }
   [i, ans]: 1 0
   {
   [id, u, b, e]: 2 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [id, u, b, e]: 2 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [id, u, b, e]: 2 4 1 2
      [tree_mul[u], tree_add[u]]: 1 0
      {
        [id, u, b, e]: 2 8 1 1
      }
      {
        [id, u, b, e]: 2 9 2 2
        [tree_mul[u], tree_add[u]]: 1000 123
        [ret]: 123
      }
      [ret]: 123
    }
    {
      [id, u, b, e]: 2 5 3 3
    }
    [ret]: 123
   }
   {
    [id, u, b, e]: 2 3 4 5
   }
   [ret]: 123
   }
   [i, ans]: 2 0
   {
   [id, u, b, e]: 3 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [id, u, b, e]: 3 2 1 3
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [id, u, b, e]: 3 4 1 2
    }
    {
      [id, u, b, e]: 3 5 3 3
      [tree_mul[u], tree_add[u]]: 10000 1232
      [ret]: 1232
    }
    [ret]: 1232
   }
   {
    [id, u, b, e]: 3 3 4 5
   }
   [ret]: 1232
   }
   [i, ans]: 3 0
   {
   [id, u, b, e]: 4 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [id, u, b, e]: 4 2 1 3
   }
   {
    [id, u, b, e]: 4 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [id, u, b, e]: 4 6 4 4
      [tree_mul[u], tree_add[u]]: 1000 132
      [ret]: 132
    }
    {
      [id, u, b, e]: 4 7 5 5
    }
    [ret]: 132
   }
   [ret]: 132
   }
   [i, ans]: 4 0
   {
   [id, u, b, e]: 5 1 1 5
   [tree_mul[u], tree_add[u]]: 1 0
   {
    [id, u, b, e]: 5 2 1 3
   }
   {
    [id, u, b, e]: 5 3 4 5
    [tree_mul[u], tree_add[u]]: 1 0
    {
      [id, u, b, e]: 5 6 4 4
    }
    {
      [id, u, b, e]: 5 7 5 5
      [tree_mul[u], tree_add[u]]: 1000 123
      [ret]: 123
    }
    [ret]: 123
   }
   [ret]: 123
   }
   [i, ans]: 5 0

 */