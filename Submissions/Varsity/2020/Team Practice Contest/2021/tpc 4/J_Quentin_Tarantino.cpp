#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    scanf("%d", &n);

    vector<int> a(n), vis(n, 0);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      a[i]--;
      if (a[i] < n) vis[a[i]] = true;
    }

    printf("%s\n", !is_sorted(a.begin(), a.end()) and accumulate(vis.begin(), vis.end(), 0) == n ? "yes" : "no");
  }

  return 0;
}