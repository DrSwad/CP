#include <bits/stdc++.h>
using namespace std;

const int N = 2e5 + 5;

int n;
vector<int> cmp;

int f[N];
void update(int p, int v) {
  while (p <= n) f[p] += v, p += p & -p;
}
int pref(int p) {
  int ret = 0;
  while (p) ret += f[p], p -= p & -p;
  return ret;
}

void reset() {
  for (int i = 1; i <= n; i++) f[i] = 0;
  n = 0;
  cmp.clear();
}

void test_case() {
  cin >> n;

  vector<int> a(n);
  for (int &i : a) {
    cin >> i;
    cmp.push_back(i);
  }

  sort(cmp.begin(), cmp.end());
  cmp.resize(unique(cmp.begin(), cmp.end()) - cmp.begin());
  n = cmp.size();

  long long ans = 0;

  for (int x : a) {
    int v = lower_bound(cmp.begin(), cmp.end(), x) - cmp.begin();
    v++;

    int small = pref(v - 1);
    int big =  pref(n) - pref(v);
    ans += min(small, big);

    update(v, 1);
  }

  cout << ans << "\n";

  reset();
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