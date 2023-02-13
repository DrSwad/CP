#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  ll sum = 0;
  for (int i : a) sum += i;

  int all = 0;
  map<int, int> replace;
  for (int i = 0; i < n; i++) {
    replace[i] = a[i];
  }

  while (q--) {
    int t;
    cin >> t;

    if (t == 1) {
      int i, x;
      cin >> i >> x;
      i--;

      if (replace.find(i) != replace.end()) {
        sum -= replace[i];
      }
      else {
        sum -= all;
      }
      replace[i] = x;
      sum += replace[i];
    }
    else {
      int x;
      cin >> x;
      all = x;
      sum = (ll)x * n;
      replace.clear();
    }

    cout << sum << "\n";
  }

  return 0;
}