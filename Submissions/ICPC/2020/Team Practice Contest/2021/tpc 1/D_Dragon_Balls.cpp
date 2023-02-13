#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 3;
  map<long long, int> freq;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      freq[i * 1ll * i + j * 1ll * j]++;
    }
  }
  int mx = 0;
  for (auto [i, j] : freq) mx = max(mx, j);
  debug() << name(mx);

  return 0;
}