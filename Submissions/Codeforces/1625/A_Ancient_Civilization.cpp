#include <bits/stdc++.h>
using namespace std;

void test_case() {
    int n, l;
    cin >> n >> l;

    vector<int> a(n);
    for (int &i : a) cin >> i;

    int ans = 0;

    for (int b = 0; b < l; b++) {
        int cnt[2]{0, 0};
        for (int i = 0; i < n; i++) {
            cnt[a[i] >> b & 1]++;
        }

        ans += (1 << b) * (cnt[1] > cnt[0]);
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