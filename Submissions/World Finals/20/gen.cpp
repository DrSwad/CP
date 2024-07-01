#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// random in in [l, r)
int get_random(int l, int r) {
  return uniform_int_distribution<int>(l, r - 1)(rng);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, c;
  n = get_random(5, 10);
  c = get_random(1, 10);

  cout << n << " " << c << "\n";

  for (int i = 1; i < n; i++) {
    int u = i, v, s;
    v = get_random(u + 1, n + 1);
    s = get_random(1, 10);
    cout << u << " " << v << " " << s << "\n";
  }

  return 0;
}