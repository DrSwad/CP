#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;
  sort(a.begin(), a.end());

  int ans;
  for (ans = 0; binary_search(a.begin(), a.end(), ans); ans++);

  cout << ans << "\n";

  return 0;
}