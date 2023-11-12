#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n, mex, max_val;
  cin >> n >> mex >> max_val;

  vector<int> a(n);
  if (n<mex or mex - 1> max_val) {
    cout << "-1\n";
    return;
  }
  int sum = 0;
  for (int i = 0; i < mex; i++) sum += i;
  for (int i = mex; i < n; i++) {
    if (max_val == mex) sum += max_val - 1;
    else sum += max_val;
  }

  cout << sum << "\n";
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