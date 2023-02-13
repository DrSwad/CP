#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  int b = a.back();
  a.pop_back();

  int low = lower_bound(a.begin(), a.end(), b / 2) - a.begin();

  int c;
  if (low == 0) c = a[low];
  else if (low >= a.size()) c = a[low - 1];
  else if (abs(a[low] - b / 2) <= abs(a[low - 1] - b / 2)) c = a[low];
  else c = a[low - 1];

  cout << b << " " << c << "\n";

  return 0;
}