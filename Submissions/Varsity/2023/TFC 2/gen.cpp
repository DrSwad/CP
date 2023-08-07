#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_random(int l, int r) {
  return l + uniform_int_distribution<int>(0, r - l)(rng);
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n = get_random(1, 10);
  int k = get_random(1, n);
  cout << n << " " << k << "\n";

  for (int i = 0; i < n; i++) {
    if (i) cout << " ";
    cout << get_random(-1e9, 1e9);
  }
  cout << "\n";

  return 0;
}