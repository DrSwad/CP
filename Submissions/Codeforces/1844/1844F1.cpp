#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, c;
  cin >> n >> c;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());
  vector<int> b;

  if (c >= 0) {
    b = a;
  }
  else {
    c = -c;
    while (!a.empty()) {
      long long tot = 0;
      for (int i = 0; i < n - 1; i++) {
        tot += abs(a[i + 1] - a[i] - c);
      }

      long long best = LLONG_MAX;
      int best_index = -1;

      for (int i = 0; i < n; i++) {
        long long cur = tot;
        if (i < n - 1) cur -= abs(a[i + 1] - a[i] - c);
        if (i > 0) cur -= abs(a[i] - a[i - 1] - c);
        if (i > 0 and i < n - 1) cur += abs(a[i + 1] - a[i - 1] - c);
        if (cur < best) {
          best = cur;
          best_index = i;
        }
      }

      assert(best_index != -1);
      b.push_back(a[best_index]);
      a.erase(a.begin() + best_index);
      n--;
    }
  }

  for (int i = 0; i < b.size(); i++) {
    if (i) cout << " ";
    cout << b[i];
  }
  cout << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    test_case();
  }

  return 0;
}