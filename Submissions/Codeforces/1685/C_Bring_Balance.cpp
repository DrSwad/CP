#include <bits/stdc++.h>
using namespace std;

void test_case() {
  int n;
  cin >> n;
  n *= 2;

  string s;
  cin >> s;

  vector<int> v;
  v.push_back(0);
  for (char c : s) {
    if (c == '(') v.push_back(v.back() + 1);
    else v.push_back(v.back() - 1);
  }

  if (*min_element(v.begin(), v.end()) >= 0) {
    cout << "0\n";
    return;
  }

  int mxv = 0, mxi = -1;
  for (int i = 0; i <= n; i++) {
    if (v[i] >= mxv) {
      mxv = v[i];
      mxi = i;
    }
  }

  int mn1 = -1;
  for (int i = 0; i < mxi; i++) {
    if (v[i] < 0) {
      mn1 = i;
      break;
    }
  }
  if (mn1 == -1) {
    cout << "1\n";
    cout << mxi + 1 << " " << n << "\n";
    return;
  }

  int mn2 = -1;
  for (int i = mxi + 1; i <= n; i++) {
    if (v[i] < 0) {
      mn2 = i;
    }
  }
  if (mn2 == -1) {
    cout << "1\n";
    cout << 1 << " " << mxi << "\n";
    return;
  }

  int mx1v = -1, mx1i = -1;
  for (int i = 0; i < mn1; i++) {
    if (v[i] > mx1v) {
      mx1v = v[i];
      mx1i = i;
    }
  }

  int mx2v = -1, mx2i = -1;
  for (int i = n; i > mn2; i--) {
    if (v[i] > mx2v) {
      mx2v = v[i];
      mx2i = i;
    }
  }

  if (v[mx1i] >= v[mxi] - v[mx2i]) {
    cout << "1\n";
    cout << mx1i + 1 << " " << mx2i << "\n";
    return;
  }

  cout << "2\n";
  cout << 1 << " " << mxi << "\n";
  cout << mxi + 1 << " " << n << "\n";
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