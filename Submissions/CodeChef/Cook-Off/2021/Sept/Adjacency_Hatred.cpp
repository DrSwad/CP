#include <bits/stdc++.h>
using namespace std;

bool check(const vector<int> &a) {
  int ret = 0;
  for (int i = 1; i < a.size(); i++) {
    ret += abs(a[i] - a[i - 1]) % 2;
  }
  return ret % 2 == 1;
}

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  for (int i = 1; i < n; i++) {
    if (a[i] % 2 != a[0] % 2) {
      swap(a[1], a[i]);
      break;
    }
  }

  if (!check(a)) swap(a[0], a[1]);
  if (!check(a)) cout << "-1\n";
  else {
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << a[i];
    }
    cout << "\n";
  }
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