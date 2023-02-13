#include <bits/stdc++.h>
using namespace std;

const int A = int(1e9) + 5;

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  auto get_ans = [&]() {
    int prv = A;
    int ans = 0;
    for (int i = 0; i < n; i++) {
      if (a[i] < prv) {
        ans++;
        prv = a[i];
      }
    }
    return ans;
  };

  while (m--) {
    int k, d;
    cin >> k >> d;
    k--;

    a[k] -= d;

    cout << get_ans();
    if (m) cout << " ";
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