#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, k;
  cin >> n >> k;

  vector<int> s(n);
  for (int &i : s) cin >> i;

  map<int, int> f;
  for (int i : s) f[i]++;

  int rem = n;
  int cap = k;
  for (auto [s, freq] : f) {
    if (freq > 2) {
      cout << "NO\n";
      return;
    }
    else if (freq == 2) {
      rem -= 2;
      cap--;
    }
  }

  cout << (cap >= (rem + 1) / 2 ? "YES\n" : "NO\n");
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}