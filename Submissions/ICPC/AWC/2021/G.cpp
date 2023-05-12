#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, x;
  cin >> n >> x;

  vector<int> e(n);
  for (int &i : e) cin >> i;

  vector<ll> mx(n, 0);
  for (int i = 1; i < n; i++) {
    mx[i] = mx[i - 1];
    if (e[i - 1] > 0) mx[i] += e[i - 1];
  }

  stack<int> ans;
  ll sum = x;

  for (int i = n - 1; i >= 0; i--) {
    ll new_sum = sum + e[i];
    if (new_sum + mx[i] >= 0) {
      ans.push(i);
      sum = new_sum;
    }
  }

  cout << ans.size() << "\n";
  while (!ans.empty()) {
    cout << ans.top() + 1;
    ans.pop();
    if (!ans.empty()) cout << " ";
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