#include <bits/stdc++.h>
using namespace std;

template<typename T>
int LIS(const vector<T> &a, bool strict) {
  vector<T> v;
  for (const T &i : a) {
    auto it = strict ? lower_bound(v.begin(), v.end(), i) : upper_bound(v.begin(), v.end(), i);
    if (it != v.end()) *it = i;
    else v.push_back(i);
  }
  return v.size();
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  reverse(a.begin(), a.end());
  cout << LIS(a, false) << "\n";

  return 0;
}