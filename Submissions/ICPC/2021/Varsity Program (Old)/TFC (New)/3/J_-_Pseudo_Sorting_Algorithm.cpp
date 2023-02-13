#include <bits/stdc++.h>
using namespace std;

const int A = 1e5 + 5;

void test_case() {
  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  a.insert(a.begin(), 0);
  a.push_back(A);
  n += 2;

  vector<int> b;
  for (int i = 0; i < n; i++) {
    if (b.empty()) b.push_back(i);
    else if (a[i] >= a[b.back()]) b.push_back(i);
  }

  assert(b.size() >= 2);
  int ans = b.size();

  for (int i = 1; i < b.size() - 1; i++) {
    int st = b[i], en = b[i + 1];

    vector<int> c{b[i - 1]};
    for (int j = st + 1; j < en; j++) {
      if (a[j] >= a[c.back()]) c.push_back(j);
    }

    int bi = lower_bound(b.begin() + i + 1, b.end(), c.back(), [&](int i, int j) { return a[i] < a[j];}) - b.begin();
    int curr = b.size() - 2 + c.size() - (bi - (i + 1));
    ans = max(ans, curr);
  }

  cout << ans - 2 << "\n";
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