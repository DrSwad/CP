#include <bits/stdc++.h>
using namespace std;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch())
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

const int MX = 2e6;

bool go(vector<int> &v, int need) {
  shuffle(v.begin(), v.end(), rng);
  int g = 0;
  for (int i = 0; i < need; i++) {
    g = gcd(g, v[i]);
  }
  return g == 1;
}

void test_case() {
  int n;
  cin >> n;
  int m = (n + 1) / 2;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> b;
  for (int i : a) {
    if (i % 2 == 0) {
      b.push_back(i / 2);
    }
  }
  a = b;
  n = a.size();

  if (n < m) {
    cout << "NO\n";
    return;
  }

  if (m == 1) {
    cout << (find(a.begin(), a.end(), 1) != a.end() ? "YES" : "NO") << "\n";
    return;
  }

  int trials = MX / n;
  while (trials--) {
    if (go(a, m)) {
      cout << "YES\n";
      return;
    }
  }

  cout << "NO" << "\n";
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