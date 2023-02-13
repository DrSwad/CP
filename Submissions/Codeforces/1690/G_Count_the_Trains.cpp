#include <bits/stdc++.h>
using namespace std;

const int BLK_SZ = 350;
const int A = int(1e9) + 5;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b(n);
  int prv = A;
  for (int i = 0; i < n; i++) {
    b[i] = min(a[i], prv);
    prv = b[i];
  }

  int tot_blk = (n + BLK_SZ - 1) / BLK_SZ;
  vector<int> blk_ans(tot_blk), blk_left(tot_blk), blk_right(tot_blk);

  auto blk_left_id = [&](int blki) { return blki * BLK_SZ; };
  auto blk_right_id = [&](int blki) { return min((blki + 1) * BLK_SZ, n) - 1; };
  auto blk_id = [&](int id) { return id / BLK_SZ; };
  auto b_value = [&](int id) {
    int blki = blk_id(id);
    return b[id] <= blk_left[blki] ? b[id] : (b[id] = blk_left[blki]);
  };
  auto recalc_blk_answer = [&](int blki) {
    blk_ans[blki] = 0;
    int prv = A;
    int blk_l = blk_left_id(blki);
    int blk_r = blk_right_id(blki);
    for (int i = blk_l; i <= blk_r; i++) {
      int bi = b_value(i);
      assert(bi <= prv);
      if (bi < prv) {
        prv = bi;
        blk_ans[blki]++;
      }
    }
  };

  for (int blki = 0; blki < tot_blk; blki++) {
    blk_left[blki] = b[blk_left_id(blki)];
    blk_right[blki] = b[blk_right_id(blki)];
    recalc_blk_answer(blki);
  }

  auto update_blk = [&](int blki, int val) {
    if (val >= blk_left[blki]) return false;

    if (val <= blk_right[blki]) {
      blk_left[blki] = blk_right[blki] = val;
      blk_ans[blki] = 1;
      return true;
    }

    int blk_l = blk_left_id(blki);
    int blk_r = blk_right_id(blki);
    for (int i = blk_l; i <= blk_r; i++) {
      int curr = b_value(i);
      if (curr < val) break;
      b[i] = val;
    }
    blk_left[blki] = min(blk_left[blki], b[blk_l]);
    blk_right[blki] = min(blk_right[blki], b[blk_r]);
    recalc_blk_answer(blki);

    return false;
  };

  auto update = [&](int id, int val) {
    int at_blk = blk_id(id);
    int blk_l = blk_left_id(at_blk);
    int blk_r = blk_right_id(at_blk);
    for (int i = id; i <= blk_r; i++) {
      b[i] = min(b[i], val);
    }

    blk_left[at_blk] = min(blk_left[at_blk], b[blk_l]);
    blk_right[at_blk] = min(blk_right[at_blk], b[blk_r]);
    recalc_blk_answer(at_blk);

    for (int blki = at_blk + 1; blki < tot_blk; blki++) {
      if (!update_blk(blki, val)) break;
    }
  };

  auto tot_ans = [&]() {
    int prv = A;
    int ans = 0;
    for (int blki = 0; blki < tot_blk; blki++) {
      ans += blk_ans[blki];
      if (blk_left[blki] == prv) ans--;
      prv = blk_right[blki];
    }
    return ans;
  };

  while (m--) {
    int k, d;
    cin >> k >> d;
    k--;

    a[k] -= d;
    update(k, a[k]);

    cout << tot_ans();
    if (m) cout << " ";
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}