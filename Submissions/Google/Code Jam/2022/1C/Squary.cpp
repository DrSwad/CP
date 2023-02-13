#include <bits/stdc++.h>
using namespace std;

void solve1(int n, int k, vector<int> a) {
  long long p = 0, s = 0;
  for (int i = 0; i < n; i++) {
    s += a[i];
    for (int j = i + 1; j < n; j++) {
      p += 1ll * a[i] * a[j];
    }
  }

  if (p == 0) cout << "0\n";
  else if (s == 0 or abs(p) % abs(s) != 0) cout << "IMPOSSIBLE\n";
  else cout << p / -s << "\n";
}

void solve2(int n, int k, vector<int> a) {
  long long p = 0, s = 0;
  for (int i = 0; i < n; i++) {
    s += a[i];
    p += a[i] * a[i];
  }

  cout << (1 - s) << " ";
  p += 1ll * (1 - s) * (1 - s);
  s += (1 - s);

  long long d = p - s;
  assert(d % 2 == 0);
  cout << d / 2 << "\n";
}

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (k == 1) return solve1(n, k, a);
  else return solve2(n, k, a);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}