#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

bool check(int mask) {
  int rmask = 0;

  vector<int> order;
  for (int i = 0; i < n; i++) {
    if (mask >> i & 1) {
      order.push_back(i);
    }
  }

  for (int i = 0; i < (int)order.size() - 1; i++) {
    if (a[order[i]] > a[order[i + 1]]) return false;
  }

  for (int i : order) {
    for (int j = 0; j < n; j++) {
      if (i == j or ((i < j) != (a[i] < a[j]))) {
        rmask |= 1 << j;
      }
    }
  }

  return rmask == (1 << n) - 1;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    scanf("%d", &n);
    a.resize(n);
    for (int &i : a) scanf("%d", &i);

    int ans = n;
    for (int mask = 1; mask < 1 << n; mask++) {
      if (check(mask)) {
        if (__builtin_popcount(mask) < ans) {
          cerr << bitset<8>(mask).to_string() << endl;
        }
        ans = min(ans, __builtin_popcount(mask));
      }
    }

    printf("%d\n", ans);
  }

  return 0;
}