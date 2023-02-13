#include <bits/stdc++.h>
using namespace std;

map<vector<int>, int> dp;

int grundy(int n, vector<int> a) {
  if (dp.find(a) != dp.end()) return dp[a];
  bool flag = a == vector<int>{15, 12, 18, 18, 18, 16, 11, 20, 15};
  vector<int> st;
  for (int i = 0; i < n - 1; i++) {
    int j = i + 1;
    int g = gcd(a[i], a[j]);
    if (g > 1) {
      int val_i = a[i], val_j = a[j];
      a[i] /= g, a[j] /= g;
      st.push_back(grundy(n, a));
      a[i] = val_i, a[j] = val_j;
    }
  }
  sort(st.begin(), st.end());
  st.resize(unique(st.begin(), st.end()) - st.begin());
  int mex = 0;
  while (mex < st.size() and st[mex] == mex) mex++;
  return dp[a] = mex;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;
  vector<int> a(n);
  for (int &i : a) cin >> i;

  if (grundy(n, a)) cout << "Alice\n";
  else cout << "Bob\n";

  return 0;
}