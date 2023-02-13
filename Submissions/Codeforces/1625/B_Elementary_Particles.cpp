#include <bits/stdc++.h>
using namespace std;

void test_case() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) cin >> i;

    int ans = -1;
    map<int, int> last_pos;

    for (int i = n - 1; i >= 0; i--) {
        if (last_pos.find(a[i]) != last_pos.end()) {
            ans = max(ans, 1 + i + (n - 1 - last_pos[a[i]]));
        }

        last_pos[a[i]] = i;
    }

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