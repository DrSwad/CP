#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;

  long long d, c, m;
  cin >> d >> c >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int df = 0;
  for (int i = 0; i < n; i++) {
    if (a[i] == 1) {
      if (d == 0) break;
      d--, df++, c += m;
    }
    else {
      if (c == 0) break;
      c--;
    }
  }

  int td = count(a.begin(), a.end(), 1);
  cout << (df >= td ? "YES" : "NO") << "\n";
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int t = 1;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    cout << "Case #" << cs << ": ";
    test_case();
  }

  return 0;
}