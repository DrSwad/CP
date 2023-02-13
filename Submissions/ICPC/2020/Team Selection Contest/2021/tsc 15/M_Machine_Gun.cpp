#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;
const int BASE = 5782344;
const int N = 1e5 + 5;
int pow_base[N];

int n;
int x[N], y[N];

int a[N];
vector<int> tree[N << 2];

inline bool comp1(int i, int j) {
  return 2ll * y[i] - (ll)x[i] < 2ll * y[j] - (ll)x[j];
}

inline bool comp2(int i, int j) {
  return 2ll * y[i] + (ll)x[i] < 2ll * y[j] + (ll)x[j];
}

void init(int u = 1, int b = 1, int e = n) {
  if (b == e) return void(tree[u].push_back(a[b]));

  int mid = b + e >> 1;
  init(u << 1, b, mid), init(u << 1 | 1, mid + 1, e);

  auto &lt = tree[u << 1], &rt = tree[u << 1 | 1];
  auto &ct = tree[u];
  for (int i = 0, j = 0; i < lt.size() or j < rt.size();) {
    if (i == lt.size() or (j != rt.size() and comp2(rt[j], lt[i]))) {
      ct.push_back(rt[j++]);
    } else {
      ct.push_back(lt[i++]);
    }
  }
}

vector<int> vq;
void query(int l, int r, int u = 1, int b = 1, int e = n) {
  if (b > r or e < l) {
    return;
  }

  if (b >= l and e <= r) {
    auto it = lower_bound(tree[u].begin(), tree[u].end(), 0, comp2);
    while (it != tree[u].end()) {
      vq.push_back(*it);
      it++;
    }
    return;
  }

  int mid = b + e >> 1;
  query(l, r, u << 1, b, mid);
  query(l, r, u << 1 | 1, mid + 1, e);
}

int main() {
  pow_base[0] = 1;
  for (int i = 1; i < N; i++) {
    pow_base[i] = (ll)pow_base[i - 1] * BASE % MOD;
  }

  int q;
  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    scanf("%d %d", &x[i], &y[i]);
  }

  iota(a + 1, a + n + 1, 1);
  sort(a + 1, a + n + 1, comp1);

  init();

  int ans = 0;
  while (q--) {
    vq.clear();

    int A, B;
    scanf("%d %d", &A, &B);
    int xq = -1 - (ans + A) % MOD;
    int yq = (ans + B) % MOD;
    x[0] = xq;
    y[0] = yq;

    ans = 0;
    int till = upper_bound(a + 1, a + n + 1, 0, comp1) - a - 1;
    if (till >= 1) {
      query(1, till);
      sort(vq.begin(), vq.end());
      for (int j = 0; j < vq.size(); j++) {
        int i = vq[j];
        (ans += (ll)i * pow_base[j] % MOD) %= MOD;
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}