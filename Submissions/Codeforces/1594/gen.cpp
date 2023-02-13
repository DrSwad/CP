#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  typedef long long ll;
  const int K = 60;
  const int N = 2000;

  int k = rnd.next(K) + 1;
  k = K;
  ll tot = (1ll << k) - 1;
  int n = rnd.next(min(tot, (ll)N)) + 1;

  cout << k << "\n" << n << "\n";

  vector<string> colors = {"white", "yellow", "green", "blue", "red", "orange"};
  ll L = 1, R = tot - (n - 1);
  while (n--) {
    L = rnd.next(R - L + 1) + L;
    cout << L << " " << colors[rnd.next(colors.size())] << "\n";
    L++, R++;
  }

  return 0;
}