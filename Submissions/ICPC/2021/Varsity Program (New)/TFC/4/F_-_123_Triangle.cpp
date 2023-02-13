#include <bits/stdc++.h>
using namespace std;

bool binom_parity(int a, int b) {
  return (a & b) == b;
}

int solve01(vector<int> v) {
  int n = v.size();
  int ret = 0;
  for (int i = 0; i < n; i++) {
    if (v[i] % 2 == 1 and binom_parity(n - 1, i) == 1) ret ^= 1;
  }
  return ret;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  string s;
  cin >> s;

  vector<int> v(n);
  for (int i = 0; i < n; i++) v[i] = s[i] - '0';

  vector<int> nv;
  for (int i = 0; i < n - 1; i++) {
    nv.push_back(abs(v[i + 1] - v[i]));
  }
  swap(v, nv);
  n--;

  if (solve01(v) == 1) cout << "1\n";
  else if (find(v.begin(), v.end(), 1) != v.end()) cout << "0\n";
  else {
    for (int &i : v) i /= 2;
    if (solve01(v) == 1) cout << "2\n";
    else cout << "0\n";
  }

  return 0;
}