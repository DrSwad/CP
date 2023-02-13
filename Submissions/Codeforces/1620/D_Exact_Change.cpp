#include <bits/stdc++.h>
using namespace std;

int min3(int f1, int f2, int a) {
  int mn = -1;

  for (int c1 = 0; c1 <= f1; c1++) {
    for (int c2 = 0; c2 <= f2; c2++) {
      int v = c1 * 1 + c2 * 2;
      if (v <= a and (a - v) % 3 == 0) {
        int curr = (a - v) / 3;
        mn = mn == -1 ? curr : min(mn, curr);
      }
    }
  }

  return mn;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int ans = -1;

  for (int f1 = 0; f1 <= 2; f1++) {
    for (int f2 = 0; f2 <= 3; f2++) {
      bool possible = true;
      int max3 = 0;
      for (int i : a) {
        int curr = min3(f1, f2, i);
        if (curr == -1) possible = false;
        max3 = max(max3, curr);
      }
      if (possible) {
        int curr = max3 + f1 + f2;
        ans = ans == -1 ? curr : min(ans, curr);
      }
    }
  }

  assert(ans != -1);
  cout << ans << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}