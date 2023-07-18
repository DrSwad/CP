#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_random(int l, int r) {
  return uniform_int_distribution<int>(l, r)(rng);
}

int main(int argc, char *argv[]) {
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 5;
  const int K = 1 << 2;

  int n = get_random(1, N);
  cout << n << "\n";

  vector<int> a(n);
  for (int &i : a) i = get_random(0, K - 1);
  for (int i : a) cout << i << " ";
  cout << "\n";

  for (int i = 2; i <= n; i++) {
    cout << i << " " << get_random(1, i - 1) << "\n";
  }

  return 0;
}