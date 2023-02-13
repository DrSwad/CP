#include <bits/stdc++.h>
using namespace std;

bool is_prime(int n) {
  if (n <= 1) return false;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

void answer(vector<int> ans) {
  cout << ans.size() << "\n";
  for (int i = 0; i < ans.size(); i++) {
    if (i) cout << " ";
    cout << ans[i] + 1;
  }
  cout << "\n";
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<int> ans(n);
  iota(ans.begin(), ans.end(), 0);

  int sum = accumulate(a.begin(), a.end(), 0);
  if (is_prime(sum)) {
    for (int i = 0; i < n; i++) {
      sum -= a[i];
      if (!is_prime(sum)) {
        ans.erase(ans.begin() + i);
        break;
      }
      sum += a[i];
    }
  }

  answer(ans);
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}