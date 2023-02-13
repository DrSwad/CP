#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 1e5;
  const int A = 1e9;
  const int M = 1e5;

  int t = 1;
  cout << t << "\n";

  while (t--) {
    int n = rnd.next(1, N);

    vector<int> a(n);
    for (int &i : a) i = rnd.next(1, A);

    vector<pair<int, int>> q;
    vector<int> aa = a;
    while (true) {
      int mn = *min_element(aa.begin(), aa.end());
      if (mn == 0) break;

      int do_more = rnd.next(1, M);
      if (do_more == M) break;

      int k = rnd.next(n);
      int d = rnd.next(aa[k] + 1);
      q.push_back({k, d});
      aa[k] -= d;
    }

    cout << n << " " << q.size() << "\n";
    for (int i : a) cout << i << " ";
    cout << "\n";
    for (auto [k, d] : q) {
      cout << k + 1 << " " << d << "\n";
    }
  }

  return 0;
}