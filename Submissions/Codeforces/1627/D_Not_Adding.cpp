#include <bits/stdc++.h>
using namespace std;

const int N = 1e6 + 5;

int n;
int a[N];
bool vis[N];

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  for (int i = 1; i <= n; i++) {
    cin >> a[i];
    vis[a[i]] = true;
  }

  int ans = -n;

  for (int at = N - 1; at >= 1; at--) {
    int g = -1;
    for (int mul = at; mul < N; mul += at) {
      if (vis[mul]) {
        if (g == -1) g = mul;
        else g = gcd(g, mul);
      }
    }
    vis[at] = g == at;
    ans += vis[at];
  }

  cout << ans << endl;

  return 0;
}