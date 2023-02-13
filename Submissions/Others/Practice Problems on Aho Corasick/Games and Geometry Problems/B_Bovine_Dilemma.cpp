#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> x(n);
    for (int &i : x) scanf("%d", &i);

    map<int, int> dist;
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        dist[abs(x[i] - x[j])]++;
      }
    }

    printf("%d\n", dist.size());
  }

  return 0;
}