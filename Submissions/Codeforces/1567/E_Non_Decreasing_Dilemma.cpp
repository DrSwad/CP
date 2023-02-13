#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 2e5 + 5;

int n, q;
int a[N];
set<int> L;
int len[N];
ll rc[N];

ll f[N];
ll pref(int p) {
  ll ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}
void update(int p, ll new_v) {
  ll curr_v = pref(p) - pref(p - 1);
  ll v = new_v - curr_v;
  while (p <= n) f[p] += v, p += p & -p;
}
ll range(int l, int r) {
  return pref(r) - pref(l - 1);
}

ll inline contrib(ll len) {
  return len * (len + 1) / 2;
}

void add_range(int l, ll _len) {
  L.insert(l);
  len[l] = _len;
  rc[l] = contrib(len[l]);
  update(l, rc[l]);
}

void remove_range(int l) {
  L.erase(l);
  len[l] = 0;
  rc[l] = contrib(len[l]);
  update(l, 0);
}

void split(int x) {
  auto it_prv = L.upper_bound(x);
  it_prv--;
  int pL = *it_prv;
  int nL = pL + len[pL];

  if (pL < x) {
    add_range(pL, x - pL);
  }

  if (x + 1 < nL) {
    add_range(x + 1, nL - (x + 1));
  }

  add_range(x, 1);
}

bool try_merge(int l1) {
  if (l1 < 1) return false;

  int l2 = l1 + len[l1];
  if (l2 > n) return false;

  if (a[l2 - 1] <= a[l2]) {
    int l3 = l2 + len[l2];

    remove_range(l2);
    add_range(l1, l3 - l1);

    return true;
  }
  else return false;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  cin >> n >> q;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }

  for (int l = 1; l <= n; ) {
    int r = l + 1;
    while (r <= n and a[r] >= a[r - 1]) r++;

    L.insert(l);
    len[l] = r - l;
    rc[l] = contrib(len[l]);
    update(l, rc[l]);

    l = r;
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int x, y;
      cin >> x >> y;
      a[x] = y;

      auto it_prv = L.upper_bound(x);
      it_prv--;
      int pL = *it_prv;
      int nL = pL + len[pL];

      split(x);

      int l = x;
      if (x > 1) {
        auto it_prv = L.find(x);
        it_prv--;
        int pL = *it_prv;

        if (try_merge(pL)) l = pL;
      }

      try_merge(l);
    } else {
      int l, r;
      cin >> l >> r;

      auto it_first = L.lower_bound(l);
      if (it_first == L.end() or * it_first > r) {
        cout << contrib(r - l + 1) << "\n";
        continue;
      }

      int firstL = *it_first;
      auto it_last = L.upper_bound(r);
      it_last--;
      int lastL = *it_last;

      ll ans = range(firstL, lastL - 1);

      ll lenL = firstL - l;
      ll lenR = r - (lastL - 1);

      ans += contrib(lenL) + contrib(lenR);
      cout << ans << "\n";
    }
  }

  return 0;
}