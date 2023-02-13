#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

seed_seq seq{
  (uint64_t)chrono::duration_cast<chrono::nanoseconds>(
    chrono::high_resolution_clock::now().time_since_epoch())
  .count(),
  (uint64_t)__builtin_ia32_rdtsc(),
  (uint64_t)(uintptr_t)make_unique<char>().get()};
mt19937 rng(seq);

int choose(int n, int k) {
  if (n<0 or k> n) return 0;
  if (k == 0 or k == n) return 1;

  int ret = 1;
  for (int i = 0; i < k; i++) {
    ret = ret * (n - i) / (i + 1);
  }
  return ret;
}

int T;
vector<int> picked;
void dfs(int n, int nn, int prv, int mx, int M) {
  if (n == 0) {
    T++;

    vector<int> npicked = picked;
    shuffle(npicked.begin(), npicked.end() - 1, rng);
    int cmask = npicked[0];
    for (int i = 1; i < nn; i++) {
      cmask *= mx;
      cmask += npicked[i];
    }
    int tot = 1;

    vector<int> medals;
    for (int i = 0; i < nn; i++) {
      for (int j = 0; j < 3; j++) {
        int v = cmask % (M + 1);
        cmask /= (M + 1);

        medals.push_back(v);
        tot += v;
      }
    }

    cout << nn << " " << (tot + 1) << "\n";
    for (int i = 0; i < nn; i++) {
      for (int j = 0; j < 3; j++) {
        if (j) cout << " ";
        cout << medals[i * 3 + j];
      }
      cout << "\n";
    }
    for (int k = 0; k <= tot; k++) cout << k << "\n";

    return;
  }

  for (int curr = n == 1 ? 0 : prv; curr < mx; curr++) {
    picked.push_back(curr);
    dfs(n - 1, nn, curr, mx, M);
    picked.pop_back();
  }
}

int main(int argc, char *argv[]) {
  registerGen(argc, argv, 1);
  ios::sync_with_stdio(false);
  cin.tie(0);

  const int N = 12, Q = 8, M = 5;
  long long K = 12;

  int t = 1;
  cout << t << "\n";

  while (t--) {
    int n = rnd.next(N) + 1, q = rnd.next(Q) + 1;
    n = q = 7;
    cout << n << " " << q << "\n";

    for (int i = 0; i < n; i++) {
      int g = rnd.next(M);
      int s = rnd.next(M);
      int b = rnd.next(M);
      cout << g << " " << s << " " << b << "\n";
    }

    while (q--) {
      cout << rnd.next(K) << "\n";
    }
  }

  /* const int M = 3, K = 4;

     int n = 4;
     int mx = (M + 1) * (M + 1) * (M + 1);
     int sum = (mx - 1) + ((n - 1) + 1);
     int items = (n - 1) + 1;
     int t = mx * choose(sum - 1, items - 1);

     cout << t << "\n";
     dfs(n, n, 0, mx, M);
     assert(t == T); */

/*   for (int mask = 0; mask < t; mask++) {
    int cmask = mask;
    int tot = 1;

    vector<int> medals;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 3; j++) {
        int v = cmask % (M + 1);
        cmask /= (M + 1);

        medals.push_back(v);
        tot += v;
      }
    }

    cout << n << " " << (tot + 1) << "\n";
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 3; j++) {
        if (j) cout << " ";
        cout << medals[i * 3 + j];
      }
      cout << "\n";
    }
    for (int k = 0; k <= tot; k++) cout << k << "\n";
   } */

  return 0;
}