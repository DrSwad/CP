#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  vector<int> sq(4, 0);

  int n;
  cin >> n;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  int p = 0;
  for (int i : a) {
    sq[0]++;
    for (int j = 3; j >= 0; j--) {
      int k = j + i;
      if (k > 3) p += sq[j], sq[j] = 0;
      else sq[k] += sq[j], sq[j] = 0;
    }
  }

  cout << p << "\n";

  return 0;
}