#include <bits/stdc++.h>
using namespace std;

void test_case() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int &i : a) cin >> i;

    vector<vector<int>> pos(n + 1);
    for (int i = 0; i < n; i++) {
        pos[a[i]].push_back(i);
    }

    vector<int> b;
    for (int at = 0; at < n; at++) {
        int nat = at;
        int xr;

        for (xr = 0; ; xr++) {
            auto it = lower_bound(pos[xr].begin(), pos[xr].end(), at);
            if (it == pos[xr].end()) break;
            nat = max(nat, *it);
        }

        b.push_back(xr);
        at = nat;
    }

    cout << b.size() << "\n";
    for (int i = 0; i < b.size(); i++) {
        if (i) cout << " ";
        cout << b[i];
    }
    cout << "\n";
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