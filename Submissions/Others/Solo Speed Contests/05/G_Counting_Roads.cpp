#include <bits/stdc++.h>
using namespace std;

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);

  int n, m;
  cin >> n >> m;

  vector<int> freq(n, 0);
  while (m--) {
    int a, b;
    cin >> a >> b;
    freq[a - 1]++;
    freq[b - 1]++;
  }

  for (int i = 0; i < n; i++) cout << freq[i] << "\n";

  return 0;
}