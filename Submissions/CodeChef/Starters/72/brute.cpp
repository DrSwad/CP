#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MOD = 1e9 + 7;

bool is_valid(const vector<int> &a) {
  int mn = MOD - 1, mx = -1;
  for (int i : a) {
    mn = min(mn, i);
    mx = max(mx, i);
    if (i != mn and i != mx) return false;
  }
  return true;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  int ans = 0;
  do {
    ans += is_valid(a);
  } while (next_permutation(a.begin(), a.end()));

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