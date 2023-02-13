#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

vector<pair<int, ll>> normalize(vector<int> a, int m) {
  vector<pair<int, ll>> ret;
  int n = a.size();
  for (int i = 0; i < n; i++) {
    int A = a[i];
    while (a[i] % m == 0) {
      a[i] /= m;
    }

    if (i > 0 and a[i] == a[i - 1]) {
      ret.back().second += A / a[i];
    }
    else {
      ret.push_back({a[i], A / a[i]});
    }
  }

  return ret;
}

void test_case() {
  int n, m;
  cin >> n >> m;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int k;
  cin >> k;

  vector<int> b(k);
  for (int &i : b) cin >> i;

  if (normalize(a, m) == normalize(b, m)) cout << "Yes\n";
  else cout << "No\n";
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