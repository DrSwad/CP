#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

ld area(ll a, ll b, ll c) {
  if (a >= b or b >= c or a + b <= c) {
    return -1;
  }
  ld s = (a + b + c) / 2.0;
  ld area = sqrt(s) * sqrt(s - a) * sqrt(s - b) * sqrt(s - c);
  return area;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, c;
    scanf("%d %d", &n, &c);

    vector<int> a(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
    }

    sort(a.begin(), a.end());

    ld ans = -1;
    for (int i = 1; i < (int)a.size() - 1; i++) {
      ld curr = area(a[0], a[i], a[i + 1]);
      ans = ans < 0 ? curr : min(ans, curr);
    }
    for (int i = 0; i < n; i++) {
      for (int j = i + 1; j < n; j++) {
        int k = lower_bound(a.begin(), a.end(), a[i] + a[j])
            - a.begin() - 1;
        if (k <= j) {
          continue;
        }
        ld curr = area(a[i], a[j], a[k]);
        ans = ans < 0 ? curr : min(ans, curr);
      }
    }

    if (ans < 0) {
      puts("-1");
    } else {
      printf("%.15Lf\n", ans);
    }
  }

  return 0;
}