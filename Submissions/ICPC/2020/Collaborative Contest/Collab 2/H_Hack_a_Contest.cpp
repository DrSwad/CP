#include <bits/stdc++.h>
using namespace std;

int main() {
  int t;
  cin >> t;

  for (int cs = 1; cs <= t; cs++) {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<int> times(n);
    for (int i = 0; i < n; i++) scanf("%d", &times[i]);

    vector<int> subs(m);
    for (int i = 0; i < m; i++) scanf("%d", &subs[i]);

    sort(times.begin(), times.end());
    sort(subs.begin(), subs.end());

    long long ans = 0;
    for (int i = 0; i < m; i++) ans += (subs[i] - 1) * 20ll;

    int sum = 0;
    for (int i = 0; i < m; i++) {
      ans += times[sum + subs[i] - 1];
      sum += subs[i];
    }

    printf("Case %d: %lld\n", cs, ans);
  }

  return 0;
}
