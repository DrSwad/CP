#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> v(n);
  for (int i = 0; i < n; i++) v[i] = s[i] - '0';

  while (n > 1) {
    vector<int> nv;
    for (int i = 0; i < n - 1; i++) {
      nv.push_back(abs(v[i + 1] - v[i]));
    }
    swap(v, nv);
    n--;
  }

  cout << v[0] << "\n";

  return 0;
}