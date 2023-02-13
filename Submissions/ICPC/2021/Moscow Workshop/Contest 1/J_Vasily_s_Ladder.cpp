#include <bits/stdc++.h>
using namespace std;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch()
    )
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> l(n), r(n);

  for (int it = 0; it < 2; it++) {
    l[0] = -1;
    for (int i = 1; i < n; i++) {
      l[i] = i - 1;
      while (l[i] > -1) {
        if (a[l[i]] > a[i]) break;
        l[i] = l[l[i]];
      }
    }
    swap(l, r);
    reverse(a.begin(), a.end());
  }
  reverse(r.begin(), r.end());
  for (int &i : r) i = (n - 1) - i;

  uniform_int_distribution<int> uid(0, 1e9);
  vector<int> b(n);
  for (int &i : b) i = uid(rng);

  vector<int> pref_a(n + 1);
  pref_a[0] = 0;
  for (int i = 0; i < n; i++) {
    pref_a[i + 1] = b[a[i] - 1] ^ pref_a[i];
  }

  vector<int> pref_b(n + 1);
  pref_b[0] = 0;
  for (int i = 0; i < n; i++) {
    pref_b[i + 1] = b[i] ^ pref_b[i];
  }

  int ans = 0;

  for (int i = 0; i < n; i++) {
    int len = a[i];
    int st, en;

    if (i - l[i] <= r[i] - i) st = l[i] + 1, en = i;
    else st = i - len + 1, en = r[i] - len;

    for (int i = max(st, 0); i <= en and i + len <= n; i++) {
      if ((pref_a[i + len] ^ pref_a[i]) == pref_b[len]) {
        ans = max(ans, len);
        break;
      }
    }
  }

  cout << ans << "\n";

  return 0;
}