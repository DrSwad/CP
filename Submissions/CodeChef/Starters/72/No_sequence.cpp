#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void test_case() {
  int n, k;
  ll s;
  cin >> n >> k >> s;

  vector<int> b;
  for (int i = 0; i < n; i++) {
    if ((s - 1) % k == 0) b.push_back(1), s = (s - 1) / k;
    else if ((s - 0) % k == 0) b.push_back(0), s = (s - 0) / k;
    else if ((s + 1) % k == 0) b.push_back(-1), s = (s + 1) / k;
    else {
      cout << "-2\n";
      return;
    }
  }

  if (s != 0) cout << "-2\n";
  else {
    for (int i = 0; i < n; i++) {
      if (i) cout << " ";
      cout << b[i];
    }
    cout << "\n";
  }
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