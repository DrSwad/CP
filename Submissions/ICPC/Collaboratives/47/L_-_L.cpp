#include <bits/stdc++.h>
using namespace std;

const int HEAP_SZ = 1e4 + 5;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int nS;
  cin >> nS;
  vector<int> S(nS);
  for (int &i : S) cin >> i;

  vector<int> grundy(HEAP_SZ);
  grundy[0] = 0;

  for (int heap_sz = 0; heap_sz < HEAP_SZ; heap_sz++) {
    vector<bool> vis(nS + 1, false);
    for (int s : S) {
      if (s <= heap_sz) {
        vis[grundy[heap_sz - s]] = true;
      }
    }

    int mex = 0;
    while (vis[mex]) mex++;

    grundy[heap_sz] = mex;
  }

  int test_cases;
  cin >> test_cases;

  while (test_cases--) {
    int total_heaps;
    cin >> total_heaps;

    int total_grundy = 0;
    while (total_heaps--) {
      int heap_sz;
      cin >> heap_sz;
      total_grundy ^= grundy[heap_sz];
    }

    if (total_grundy) cout << 'W';
    else cout << 'L';
  }

  cout << "\n";

  return 0;
}