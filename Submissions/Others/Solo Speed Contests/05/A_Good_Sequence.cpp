#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n;
  cin >> n;

  map<int, int> freq;
  while (n--) {
    int a;
    cin >> a;
    freq[a]++;
  }

  int ans = 0;
  for (auto [key, val] : freq) {
    int curr = val < key ? val : val - key;
    ans += curr;
  }

  cout << ans << "\n";

  return 0;
}