#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int A = 1e6;

bool compare(pair<int, int> p1, pair<int, int> p2) {
  int up1 = p1.first, down1 = p1.second;
  int up2 = p2.first, down2 = p2.second;
  return 1ll * up1 * down2 < 1ll * up2 * down1;
}

void test_case() {
  int n;
  cin >> n;

  pair<int, int> mn = {0, 1};
  pair<int, int> mx = {A, 1};

  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;

    pair<int, int> cur_mn = {i, b};
    pair<int, int> cur_mx = {i, a};

    mn = max(mn, cur_mn, compare);
    mx = min(mx, cur_mx, compare);
  }

  if (compare(mx, mn)) {
    cout << "-1\n";
  }
  else {
    cout << fixed << setprecision(10) << (1.0 * mn.first / mn.second) << "\n";
  }
}

int main() {
  freopen("A_in.txt", "r", stdin);
  freopen("A_out.txt", "w", stdout);

  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}