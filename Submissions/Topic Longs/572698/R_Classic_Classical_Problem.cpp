#include <bits/stdc++.h>
using namespace std;

const int P = 2e5;
bitset<2 * (P - 1)> a_bs, ans_bs, prv_ans_bs;

int binExp(int a, int e, int p) {
  int ret = 1;
  while (e) {
    if (e & 1) ret = 1ll * ret * a % p;
    a = 1ll * a * a % p, e >>= 1;
  }
  return ret;
}

int primitive_root(int p) {
  vector<int> factor;
  int tmp = p - 1;
  for (int i = 2; i * i <= tmp; ++i) {
    if (tmp % i == 0) {
      factor.emplace_back(i);
      while (tmp % i == 0) tmp /= i;
    }
  }
  if (tmp != 1) factor.emplace_back(tmp);
  for (int root = 1; ; ++root) {
    bool flag = true;
    for (int i = 0; i < (int) factor.size(); ++i) {
      if (binExp(root, (p - 1) / factor[i], p) == 1) {
        flag = false; break;
      }
    }
    if (flag) return root;
  }
}

void test_case() {
  int n, p;
  cin >> n >> p;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (find(a.begin(), a.end(), 0) == a.end()) {
    cout << "1 1\n0\n";
    return;
  }

  if (count(a.begin(), a.end(), 0) == n) {
    cout << p << " 1\n";
    for (int i = 0; i < p; i++) {
      if (i) cout << " ";
      cout << i;
    }
    cout << "\n";
    return;
  }

  if (p == 2) {
    cout << "1 2\n1\n";
    return;
  }

  int root = primitive_root(p);
  vector<int> lg(p), lg_inv(p - 1);
  for (int at = 1, exp = 0; exp < p - 1; at = 1ll * at * root % p, exp++) {
    lg[at] = exp;
    lg_inv[exp] = at;
  }

  for (int i = 0; i < n; i++) {
    if (a[i] != 0) {
      a_bs[lg[a[i]]] = a_bs[lg[a[i]] + (p - 1)] = true;
      ans_bs[lg[a[i]]] = ans_bs[lg[a[i]] + (p - 1)] = true;
    }
  }

  int mex = 1;
  while (mex < p and ans_bs.any()) {
    swap(ans_bs, prv_ans_bs);
    mex++;
    ans_bs = prv_ans_bs & (a_bs >> lg[mex]);
  }
  swap(ans_bs, prv_ans_bs);

  vector<int> ans;
  for (int i = 0; i < p - 1; i++) {
    if (ans_bs[i]) {
      ans.push_back(binExp(lg_inv[i], p - 2, p));
    }
  }
  sort(ans.begin(), ans.end());
  cout << ans.size() << " " << mex << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i];
  }
  cout << "\n";

  for (int i = 0; i < 2 * (p - 1); i++) {
    a_bs[i] = ans_bs[i] = false;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}