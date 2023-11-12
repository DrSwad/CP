#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int bigMod(int a, int e, int mod) {
  if (e == -1) e = mod - 2;
  int ret = 1;
  while (e) {
    if (e & 1) ret = (ll)ret * a % mod;
    a = (ll)a * a % mod; e >>= 1;
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
      if (bigMod(root, (p - 1) / factor[i], p) == 1) {
        flag = false; break;
      }
    }
    if (flag) return root;
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  if (n == 1) {
    cout << "YES\n1\n";
    return 0;
  }

  if (n == 2) {
    cout << "YES\n1\n2\n";
    return 0;
  }

  if (n == 4) {
    cout << "YES\n1\n3\n2\n4\n";
    return 0;
  }

  bool is_prime = true;
  for (int i = 2; i < n; i++) {
    is_prime = is_prime and n % i != 0;
  }

  if (!is_prime) {
    cout << "NO\n";
    return 0;
  }

  cout << "YES\n";

  int root = primitive_root(n);

  vector<int> ans;
  ans.push_back(1);
  for (int i = 1; i <= (n - 2) / 2; i++) {
    int x = 2 * i - 1;
    int y = (n - 2) - x;
    ans.push_back(bigMod(root, x, n));
    ans.push_back(bigMod(root, (y + n - 1) % (n - 1), n));
  }
  ans.push_back(bigMod(root, n - 2, n));
  ans.push_back(n);

  for (int i : ans) cout << i << "\n";

  return 0;
}