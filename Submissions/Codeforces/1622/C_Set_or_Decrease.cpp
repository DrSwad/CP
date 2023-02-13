#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n;
  ll k;
  cin >> n >> k;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  ll sum = 0;
  for (int i : a) sum += i;
  if (sum <= k) {
    cout << "0\n";
    return;
  }

  ll moves = sum - k;

  for (int i = n - 1; i >= 1; i--) {
    ll cmoves = n - i;
    sum -= a[i] - a[0];
    cmoves += (max(0ll, sum - k) + (n - i)) / (n - i + 1);
    moves = min(moves, cmoves);
  }

  cout << moves << "\n";
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