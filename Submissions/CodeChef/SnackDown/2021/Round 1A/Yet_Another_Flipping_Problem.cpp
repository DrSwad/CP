#include <bits/stdc++.h>
using namespace std;

inline int msb(const unsigned long long &a) { return a ? 63 - __builtin_clzll(a) : -1; }

vector<int> construct(int k, int p) {
  if (k == 1 and p == 0) return {1};
  assert(k >= 1 and k % 2 == 1 and p > 0);

  vector<int> ret;
  if (k >= 1 << p) {
    int add = 1 << p;
    vector<int> res = construct(k - add, p - 1);
    for (int i : res) ret.push_back(i + add);
    ret.push_back(1);
  }
  else {
    int add = (1 << p) - k;
    vector<int> res = construct(add, p - 1);
    for (int i : res) ret.push_back(i - add);
    ret.push_back(1 - add);
  }

  return ret;
}

void test_case() {
  int n, k;
  cin >> n >> k;

  if (k == 0) {
    cout << "YES\n0\n";
  }
  else if (k % 2 == 0) {
    cout << "NO\n";
  }
  else {
    vector<int> ans = construct(k, msb(k));
    cout << "YES\n" << ans.size() << "\n";
    for (int i : ans) cout << i << "\n";
  }
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}