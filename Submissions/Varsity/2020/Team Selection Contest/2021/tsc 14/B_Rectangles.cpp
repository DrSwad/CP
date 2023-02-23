#include <bits/stdc++.h>
using namespace std;

const int N = 1e5 + 5;
const int MOD = 1e9 + 7;

int main() {
  int t;
  cin >> t;

  vector<long long> fact(2 * N);
  fact[0] = 1;
  for (int i = 1; i < 2 * N; i++) { fact[i] = fact[i - 1] * i % MOD; }

  while (t--) {
    int n;
    scanf("%d", &n);
    n *= 2;

    vector<pair<int, int>> p(n);
    for (int i = 0; i < n; i++) {
      scanf("%d %d", &p[i].first, &p[i].second);
    }

    map<int, vector<int>> px, py;
    for (int i = 0; i < n; i++) {
      px[p[i].first].push_back(i);
      py[p[i].second].push_back(i);
    }

    set<int> sx, sy;
    int freq = 0;
    for (auto [c, v] : px) {
      freq += v.size();
      if (freq <= n / 2) {
        for (int i : v) sx.insert(i);
      } else {
        break;
      }
    }
    freq = 0;
    for (auto [c, v] : py) {
      freq += v.size();
      if (freq <= n / 2) {
        for (int i : v) sy.insert(i);
      } else {
        break;
      }
    }

    vector<int> val(4, 0);
    for (int i = 0; i < n; i++) {
      int cx = sx.find(i) != sx.end();
      int cy = sy.find(i) != sy.end();
      val[cx * 2 + cy]++;
    }

    bool flag = true;
    for (int i = 0; i < 4; i++) {
      if (val[i] != val[i ^ 3]) { flag = false; }
    }

    if (!flag) {
      puts("0");
    } else {
      printf("%lld\n", fact[val[0]] * fact[val[1]] % MOD);
    }
  }

  return 0;
}