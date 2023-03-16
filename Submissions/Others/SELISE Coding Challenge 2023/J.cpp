#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")// use avx for older judges

#include <bits/stdc++.h>
using namespace std;

const int N = 5e5 + 5;

int n;
int a[N];
vector<int> st[4 * N];

void build(int stI, int L, int R) {
  if (L == R) {
    st[stI] = vector<int>(1, a[L]);
    return;
  }

  int mid = (L + R) >> 1;
  build(stI << 1, L, mid);
  build(stI << 1 | 1, mid + 1, R);

  vector<int> &vL = st[stI << 1];
  vector<int> &vR = st[stI << 1 | 1];
  vector<int> &vC = st[stI];
  merge(vL.begin(), vL.end(), vR.begin(), vR.end(), back_insert_iterator(vC));
}

int query(int stI, int L, int R, int l, int r, int val) {
  if (l <= L && R <= r) {
    return upper_bound(st[stI].begin(), st[stI].end(), val) - st[stI].begin();
  }

  int mid = (L + R) >> 1;
  if (r <= mid) return query(stI << 1, L, mid, l, r, val);
  else if (mid + 1 <= l) return query(stI << 1 | 1, mid + 1, R, l, r, val);
  else return query(stI << 1, L, mid, l, mid, val) + query(stI << 1 | 1, mid + 1, R, mid + 1, r, val);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];

  build(1, 1, n);

  const int mx_a = *max_element(a + 1, a + n + 1);
  const int mx_k = mx_a + 1;

  int q;
  cin >> q;

  while (q--) {
    int l, r, k;
    cin >> l >> r >> k;
    if (l > r) swap(l, r);

    int add = 0;
    if (k > mx_k) add = k - mx_k, k = mx_k;

    int L = 0, R = (r - l + 1) + k;
    while (R - L > 1) {
      int mid = (R + L) / 2;
      int found = query(1, 1, n, l, r, mid);
      if (found + k <= mid) R = mid;
      else L = mid;
    }

    cout << R + add << "\n";
  }

  return 0;
}
