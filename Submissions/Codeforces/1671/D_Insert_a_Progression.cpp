#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, x;
  cin >> n >> x;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  long long ans = LLONG_MAX;
  for (int ta = 0; ta < 3; ta++) {
    for (int tb = 0; tb < 3; tb++) {
      vector<int> b = a;
      if (ta == 0) b.insert(b.begin(), 1);
      else if (ta == 1) b.insert(b.end(), 1);
      else b.insert(min_element(b.begin(), b.end()), 1);

      if (x != 1 and x > *max_element(a.begin(), a.end())) {
        if (tb == 0) b.insert(b.begin(), x);
        else if (tb == 1) b.insert(b.end(), x);
        else b.insert(max_element(b.begin(), b.end()), x);
      }

      long long curr = 0;
      for (int i = 0; i < b.size() - 1; i++) {
        curr += abs(b[i + 1] - b[i]);
      }
      ans = min(ans, curr);
    }
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