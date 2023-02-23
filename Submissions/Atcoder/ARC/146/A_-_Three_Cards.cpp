#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  sort(a.begin(), a.end());

  vector<string> s(3);
  for (int i = 0; i < 3; i++) {
    s.push_back(to_string(a[n - 1 - i]));
  }

  sort(s.begin(), s.end(), greater<string>());

  cout << s[0] + s[1] + s[2] << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int t = 1;
  // cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    // cout << "Case " << cs << ": ";
    test_case();
  }

  return 0;
}