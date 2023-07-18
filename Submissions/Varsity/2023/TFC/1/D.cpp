#include <bits/stdc++.h>
using namespace std;

const int N = 5 * 1e5 + 5;
const int mod = int(1e9) + 7;

int add(int a, int b) {
  int c = a + b;
  return c < mod ? c : c - mod;
}

int mul(int a, int b) {
  return 1ll * a * b % mod;
}

int arr[N];
int prod[4 * N];
int pref[4 * N];
int suff[4 * N];
int st[4 * N];

tuple<int, int, int, int> merge(
  int prodL,
  int prefL,
  int suffL,
  int stL,
  int prodR,
  int prefR,
  int suffR,
  int stR
) {
  int cur_prod = mul(prodL, prodR);
  int cur_pref = add(prefL, mul(prodL, prefR));
  int cur_suff = add(suffR, mul(prodR, suffL));
  int cur_st = add(stL, add(stR, mul(suffL, prefR)));
  return {cur_prod, cur_pref, cur_suff, cur_st};
}

void merge(int stI, int L, int R) {
  int mid = (L + R) / 2;
  int stL = stI << 1;
  int stR = stI << 1 | 1;
  auto [cur_prod, cur_pref, cur_suff, cur_st] = merge(
    prod[stL],
    pref[stL],
    suff[stL],
    st[stL],
    prod[stR],
    pref[stR],
    suff[stR],
    st[stR]
  );
  prod[stI] = cur_prod;
  pref[stI] = cur_pref;
  suff[stI] = cur_suff;
  st[stI] = cur_st;
}

void build(int stI, int L, int R) {
  if (L == R) {
    prod[stI] = arr[L];
    pref[stI] = arr[L];
    suff[stI] = arr[L];
    st[stI] = arr[L];
    return;
  }

  int mid = (L + R) / 2;
  build(stI << 1, L, mid);
  build(stI << 1 | 1, mid + 1, R);

  merge(stI, L, R);
}

void update(int stI, int L, int R, int at, int val) {
  if (L == R) {
    arr[L] = val;
    prod[stI] = arr[L];
    pref[stI] = arr[L];
    suff[stI] = arr[L];
    st[stI] = arr[L];
    return;
  }

  int mid = (L + R) / 2;
  if (at <= mid) update(stI << 1, L, mid, at, val);
  else update(stI << 1 | 1, mid + 1, R, at, val);

  merge(stI, L, R);
}

tuple<int, int, int, int> query(int stI, int L, int R, int l, int r) {
  tuple<int, int, int, int> ret;
  if (l <= L and R <= r) {
    ret = {prod[stI], pref[stI], suff[stI], st[stI]};
  }
  else {
    int mid = (L + R) / 2;
    if (mid < l) {
      ret = query(stI << 1 | 1, mid + 1, R, l, r);
    }
    else if (r <= mid) {
      ret = query(stI << 1, L, mid, l, r);
    }
    else {
      auto [prodL, prefL, suffL, stL] = query(stI << 1, L, mid, l, r);
      auto [prodR, prefR, suffR, stR] = query(stI << 1 | 1, mid + 1, R, l, r);
      ret = merge(
        prodL,
        prefL,
        suffL,
        stL,
        prodR,
        prefR,
        suffR,
        stR
      );
    }
  }

  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q, k;
  cin >> n >> q >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<tuple<int, int, int, int>> queries(q);
  for (int i = 0; i < q; i++) {
    auto & [p, l, r, qi] = queries[i];
    cin >> l >> r >> p;
    qi = i;
  }

  sort(queries.begin(), queries.end());

  vector<int> order_a(n);
  iota(order_a.begin(), order_a.end(), 0);
  sort(
    order_a.begin(),
    order_a.end(),
    [&](int i, int j) {
      return a[i] < a[j];
    }
  );

  for (int i = 1; i <= n; i++) {
    arr[i] = a[i - 1];
  }

  build(1, 1, n);

  vector<int> ans(q);
  int at_a = 0;

  for (auto [p, l, r, qi] : queries) {
    while (at_a < n and a[order_a[at_a]] < p) {
      update(1, 1, n, order_a[at_a] + 1, k);
      at_a++;
    }

    ans[qi] = get<3>(query(1, 1, n, l, r));
  }

  for (int i : ans) cout << i << "\n";

  return 0;
}