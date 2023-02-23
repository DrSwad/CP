#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;
const int MAX_H = 3 * 5 * 7 * 8;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, q;
  cin >> n >> q;

  vector<ll> h(n + 1);
  for (ll &i : h) cin >> i, i *= MAX_H;

  vector<ll> nh;
  nh.push_back(h[0]);
  for (int i = 1; i <= n; i++) {
    for (int j = MAX_H - 1; j >= 0; j--) {
      nh.push_back(((h[i - 1] * j) + h[i] * (MAX_H - j)) / MAX_H);
    }
  }

  cout << fixed << setprecision(10);
  while (q--) {
    int a, b;
    char c;
    cin >> a >> c >> b;
    int g = a * 10 + b;

    int ans = 0;
    int sz = nh.size();
    for (int i = 0; i < sz; i++) {
      for (int j = i + 1; j < sz; j++) {
        if (nh[j] - nh[i] >= g * (j - i)) {
          ans = max(ans, j - i);
        }
      }
    }

    if (ans) cout << ans / (ld)MAX_H << "\n";
    else cout << "-1\n";
  }

  return 0;
}