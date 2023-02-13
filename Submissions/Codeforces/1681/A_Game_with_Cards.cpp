#include <bits/stdc++.h>
using namespace std;

const int N = 51;

void test_case() {
  int n;
  cin >> n;

  vector<bool> visa(N, false);
  vector<int> a(n);
  for (int &i : a) cin >> i, visa[i] = true;

  int m;
  cin >> m;

  vector<bool> visb(N, false);
  vector<int> b(m);
  for (int &i : b) cin >> i, visb[i] = true;

  vector<bool> dpa(N + 1, false), dpb(N + 1, false);
  for (int i = N - 1; i >= 0; i--) {
    if (!visa[i]) dpa[i] = dpa[i + 1];
    else {
      dpa[i] = dpa[i + 1] or !dpb[i + 1];
    }

    if (!visb[i]) dpb[i] = dpb[i + 1];
    else {
      dpb[i] = dpb[i + 1] or !dpa[i + 1];
    }
  }

  cout << (accumulate(dpa.begin(), dpa.end(), 0) > 0 ? "Alice" : "Bob") << "\n";
  cout << (accumulate(dpb.begin(), dpb.end(), 0) > 0 ? "Bob" : "Alice") << "\n";
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