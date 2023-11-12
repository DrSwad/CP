#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n, k;
  cin >> n >> k;

  map<int, int> freq, freq2;
  while (n--) {
    int a;
    cin >> a;
    if (freq[a]) freq2[freq[a]]--;
    freq[a]++;
    freq2[freq[a]]++;
  }

  int cur = freq.size();
  int ans = 0;

  while (cur > k) {
    while (freq2.begin()->second == 0) {
      freq2.erase(freq2.begin());
    }
    cur--;
    ans += freq2.begin()->first;
    freq2.begin()->second--;
  }

  cout << ans << "\n";

  return 0;
}