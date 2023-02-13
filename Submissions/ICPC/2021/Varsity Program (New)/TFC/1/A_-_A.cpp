#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt") // use avx for older judges

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int N = 3e5 + 5;
// const int N = 10 + 5;
const int BLOCKS = 500;
// const int BLOCKS = 50;
const int MOD = 1e9 + 7;

int n, q, m;
int a[N];
int block_sz, block_cnt;
vector<int> blk_ans[BLOCKS][BLOCKS];
vector<vector<int>> pref, suff;

vector<int> merge_single(const vector<int> &v, const int a) {
  int ra = a % m;
  vector<int> ret = v;
  ret[ra] += a;
  if (ret[ra] >= MOD) ret[ra] -= MOD;

  for (int r = 0; r < m; r++) {
    int k = r + ra;
    if (k >= m) k -= m;
    ret[k] += (ll)v[r] * a % MOD;
    if (ret[k] > MOD) ret[k] -= MOD;
  }

  return ret;
}

vector<int> merge(const vector<int> &v1, const vector<int> &v2) {
  vector<int> ret(m, 0);
  for (int i = 0; i < m; i++) {
    ret[i] += v1[i];
    if (ret[i] >= MOD) ret[i] -= MOD;
    ret[i] += v2[i];
    if (ret[i] >= MOD) ret[i] -= MOD;
  }
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < m; j++) {
      int k = i + j;
      if (k >= m) k -= m;
      ret[k] += (ll)v1[i] * v2[j] % MOD;
      if (ret[k] >= MOD) ret[k] -= MOD;
    }
  }
  return ret;
}

void init() {
  pref.resize(n);
  suff.resize(n);

  block_sz = min(n, (n + BLOCKS - 1) / BLOCKS);
  block_cnt = min(BLOCKS, (n + block_sz - 1) / block_sz);

  vector<int> prv(m, 0);
  for (int i = 0, j = 0, b = 0; i < n; i++, j++) {
    if (j == block_sz) {
      j = 0, b++;
      fill(prv.begin(), prv.end(), 0);
    }
    pref[i] = merge_single(prv, a[i]);
    prv = pref[i];
  }

  fill(prv.begin(), prv.end(), 0);
  for (int i = n - 1, j = (n - 1) % block_sz, b = (n - 1) / block_sz; i >= 0; i--, j--) {
    suff[i] = merge_single(prv, a[i]);
    prv = suff[i];

    if (j == 0) {
      j = block_sz, b--;
      fill(prv.begin(), prv.end(), 0);
    }
  }

  for (int blk_l = 0; blk_l < block_cnt; blk_l++) {
    blk_ans[blk_l][blk_l] = suff[blk_l * block_sz];
    for (int blk_r = blk_l + 1; blk_r < block_cnt; blk_r++) {
      blk_ans[blk_l][blk_r] = merge(blk_ans[blk_l][blk_r - 1], suff[blk_r * block_sz]);
    }
  }
}

int query(int l, int r) {
  int blk_l = l / block_sz;
  int blk_r = r / block_sz;
  if (blk_l == blk_r) {
    vector<int> prv(m, 0);
    for (int i = l; i <= r; i++) {
      prv = merge_single(prv, a[i]);
    }
    return prv[0];
  }
  else {
    vector<int> left = suff[l];
    vector<int> middle = blk_l < blk_r  - 1 ? blk_ans[blk_l + 1][blk_r - 1] : vector<int>(m, 0);
    vector<int> right = pref[r];
    vector<int> ans = merge(merge(left, middle), right);
    return ans[0];
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  cin >> n >> q >> m;
  for (int i = 0; i < n; i++) cin >> a[i];

  init();

  while (q--) {
    int l, r;
    cin >> l >> r;
    l--, r--;
    cout << query(l, r) << "\n";
  }

  return 0;
}