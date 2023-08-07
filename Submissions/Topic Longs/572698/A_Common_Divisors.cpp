#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int mx = *max_element(a.begin(), a.end());
  vector<int> freq(mx + 1, 0);
  for (int i : a) freq[i]++;

  for (int g = mx; g >= 2; g--) {
    int cnt = 0;
    for (int mul = g; mul <= mx; mul += g) {
      cnt += freq[mul];
      if (cnt >= 2) {
        cout << g << "\n";
        return 0;
      }
    }
  }

  cout << "1\n";

  return 0;
}